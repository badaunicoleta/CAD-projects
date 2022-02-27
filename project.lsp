;;; This function changes the color of circles with radius between 4-5,
;;; hatches the circles with radius between 6-7,
;;; removes the circles with radius between 1-3,
;;;changes the radius of circles which has radius between 8-10.

(defun C:CONDCIRCLES (/ n1 n2  s1 s2 s3 s4  slen1 n b1c c1 entname slen2  b1 c d )
(setq n1 (read "7.0")) ; reads the radius for the radius changing of certain  circles
(setq n2 (read "1"))    ; reads the colorID in order to change the color of certain circles
  
;; creates the selection sets using filters
(setq s1(ssget "X" '((0 . "circle")(-4 . ">=")(40 . 4.0)(-4 . "<=")(40 . 5.0)))) ; selects all circles with radius between 4-5
(setq s2(ssget "X" '((0 . "circle")(-4 . ">=")(40 . 6.0)(-4 . "<=")(40 . 7.0)))) 
(setq s3(ssget "X" '((0 . "circle")(-4 . ">=")(40 . 1.0)(-4 . "<=")(40 . 3.0))))
(setq s4(ssget "X" '((0 . "circle")(-4 . ">=")(40 . 8.0)(-4 . "<=")(40 . 10.0))))
  
;; the color changing of the circles
  
(setq slen1 (sslength s1))   ; assigns to the variable slen1 the number of entities on the given selection set
  ; iterate over the selection set
(setq n 0)
 (repeat slen1               ; repeats the set of instructions for how many elements are in the selection set 
  (setq b1c (entget (ssname s1 n)))   ;retrieves the entity from s1
  (setq n (+ n 1))     ; next
  (setq c1 (cons 62 n2))     ; constructs the new (dotted pair) element
  (setq b1c (append b1c (list c1)))   ; transforms in a list the argument of current entity and the new (dotted pair) element
  (entmod b1c)   ; updates  the entity definition 
  )
  
;; hatching of the circles 
(setq n 0)
 (repeat (sslength s2)   ; repeats the set of instructions for how many elements are in the selection set 
   (setq entname (ssname s2 n))   ; accesses every entity from a selection set
   (command "-bhatch" "p" "solid" "s" entname "" "") ; hatch command
   (setq n(1+ n))   ; increments n with one
 )
;; removing of the circles
  (setq n 0) ; assigns to the variable n the value 0
 (repeat (sslength s3) 
   (entdel (ssname s3 n)) ; deletes an entity from a selection set
   (setq n (1+ n))
 )

;; radius changing of the circles
(setq slen2 (sslength s4)) ; assigns to the variable slen2 the number of entities on the given selection set
(setq n 0)
 (repeat slen2              ;repeats the set of instructions for how many elements are in the selection set 
  (setq b1 (entget (ssname s4 n)))   ;retrieves the entity from s4
  (setq n (+ n 1))
  (setq c (assoc 40 b1))       ; searches key 40 in the current entity
  (setq d (cons (car c) n1))   ;constructs the new (dotted pair) element with the first element from the list c and the new radius
  (setq b1 (subst d c b1))   ; modifies the entity through the replacement of the new (dotted pair) element d with c in the current entity
  (entmod b1)   ; updates  the entity definition 
 )
  
  )