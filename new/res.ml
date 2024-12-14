type token = CONST of float | LPAR | RPAR | SR | DR | EOF 
type operation = Sr | Dr
type cir = Const of float | Bin of operation * cir * cir

exception Lexical_error
exception Syntax_error
 
let is_digit c = '0' <= c && c <='9' || int_of_char c = 46

let get_number s i = assert (is_digit s.[i]);
        let j = ref i in
        while (!j < String.length s) && (is_digit s.[!j]) do
                incr j
        done;
        (CONST (float_of_string (String.sub s i (!j-i))), !j)


let rec first_token s i =
        if i = String.length s then EOF, -1
        else if is_digit s.[i] then get_number s i
        else if s.[i] = ' ' then first_token s (i+1) 
        else try List.assoc s.[i] ['(', LPAR; ')', RPAR; '-', SR; '|', DR], (i+1) 
        with Not_found -> raise Lexical_error

let rec _lexer i s  =
    match first_token s i with 
    | EOF,_ -> [EOF]
    | tok,j -> tok :: _lexer  j s

let lexer = _lexer 0

let parser_O tl = match tl with
    | SR::q -> Sr, q
    | DR::q -> Dr, q
    | _ -> raise Syntax_error

let rec parser_E tl = match tl with
  | CONST n::q -> Const n, q
  | LPAR::q -> let (ae, tlpe) = parser_B q in 
    (match tlpe with 
        | RPAR::qq -> (ae, qq) 
        | _ -> raise Syntax_error )
  | _ -> raise Syntax_error

and parser_B tl = 
  let (ae, tlpe) = parser_E tl in let (o, tlpe2) = parser_O tlpe 
  in let (ae3, tlpe3) = parser_E tlpe2 in
      Bin (o, ae, ae3), tlpe3

let parser tl = match parser_E tl with 
  |cir,[EOF]-> cir
  | _ -> raise Syntax_error


let rec __evaluate = function 
        |Const x -> x
        |Bin (Sr, x, y) -> __evaluate x +. __evaluate y
        |Bin (Dr, x, y) -> (__evaluate x *. __evaluate y) /. (__evaluate x +. __evaluate y)

let evaluate s  = __evaluate (parser(lexer s))
