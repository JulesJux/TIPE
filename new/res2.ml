type token = RES of float | LPAR | RPAR | SR | DR | EOF 
type operation = Sr | Dr
type _cir = Res of float | Bin of operation * _cir * _cir

exception Lexical_error
exception Syntax_error
 
let is_digit c = '0' <= c && c <='9' || int_of_char c = 46

let get_number s i = assert (is_digit s.[i]);
        let j = ref i in
        while (!j < String.length s) && (is_digit s.[!j]) do
                incr j
        done;
        (RES (float_of_string (String.sub s i (!j-i))), !j)


let rec first_token s i =
        if i = String.length s then EOF, -1
        else if is_digit s.[i] then get_number s i
        else if s.[i] = ' ' then first_token s (i+1) 
        else try List.assoc s.[i] ['(', LPAR; ')', RPAR; '-', SR; '|', DR], (i+1) 
        with Not_found -> raise Lexical_error

let rec _lexer i s  =
    match first_token s i with 
    | EOF,_ -> [EOF]
    | tok,j -> tok::( _lexer  j s )

let lexer =  _lexer 0

let parser_O tl = match tl with
    | SR::q -> Sr, q
    | DR::q -> Dr, q
    | _ -> raise Syntax_error

let rec parser_E tl = match tl with
  | RES n::q -> Res n, q
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


let __evaluate cir u0 = 
        let resi = ref [] in 
        let rec itot cir = match cir with
                |Res (x) -> u0/.x 
                |Bin (Sr, x, y) -> itot x +. itot y  
                |Bin (Dr, x, y) -> 1./.(1./.(itot x) +. 1./.(itot y)) 
        
        let rec cur cir = match cir with 
                |Res(x) -> []
                |Bin (Sr,x,y) -> [cur(x)]@[cur(y)] 

        let rec res cir cur curx cury = 
                match cir with
                |Res(x) -> ()
                |Bin(Sr, x, y) -> resi:=cur::cur::!resi; res x cur cur cur; res y cur cur cur
                |Bin(Dr, x, y) -> let ncurx = cur*.(curx/.(curx+.cury)) in 
                                let ncury = cur*.(cury/.(curx+.cury)) in 
                                resi:=ncurx::ncury::!resi; res x cur ncurx ncury; res y cur ncurx ncury 
                
        in itot cir  

                

let evaluate cir  = __evaluate (parser(lexer cir))

