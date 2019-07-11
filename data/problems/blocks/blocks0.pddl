

(define (problem BW-rand-5)
(:domain blocksworld)
(:objects b1 b2 b3 b4 b5 )
(:init
(on b1 b2)
(on-table b2)
(on-table b3)
(clear b1)
(clear b3)
)
(:goal
(and
(on b2 b3))
)
)


