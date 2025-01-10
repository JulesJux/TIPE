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

let round a n = let b = Float.pow 10. a in
        Float.round (n *. b) /. b;;

let __evaluate cir u0 = 
        let rec req cir = match cir with
                |Res (x) -> x
                |Bin (Sr, x, y) -> req x +. req y
                |Bin (Dr, x, y) -> 1./.(1./.(req x) +. 1./.(req y)) in
        
       let rec intensites cir i_tot = match cir with
                | Res x -> [i_tot]
                | Bin (Sr, x, y) -> (intensites x i_tot) @ (intensites y i_tot)
                | Bin (Dr, x, y) ->
                        let ix = i_tot *. (req x /. (req x +. req y)) in
                        let iy = i_tot *. (req y /. (req x +. req y)) in
                        (intensites x ix) @ (intensites y iy) in

        List.map (round 3.) (intensites cir (u0/.(req cir)))

let evaluate cir  = __evaluate (parser(lexer cir))

let test_circuit circuit u0 =
  let result = evaluate circuit u0 in
  Printf.printf "Circuit: %s\n" circuit;
  Printf.printf "Intensities: ";
  List.iter (fun x -> Printf.printf "%.3f " x) result;
  Printf.printf "\n\n"

let () =
  (* Test 1: Circuit avec une seule résistance *)
  (*test_circuit "(2)" 10.0; *) (* Par exemple, une tension de 10V *)

  (* Test 2: Circuit avec deux résistances en série *)
  test_circuit "(2 - 3)" 10.0;

  (* Test 3: Circuit avec deux résistances en parallèle *)
  test_circuit "(2 | 3)" 10.0;

  (* Test 4: Circuit avec résistances en série et parallèle *)
  test_circuit "(2 | (3 - 4))" 10.0;

  (* Test 5: Circuit avec résistances imbriquées *)
  test_circuit "((2 | 3) - 4)" 10.0

