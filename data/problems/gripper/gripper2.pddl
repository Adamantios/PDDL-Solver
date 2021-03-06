(define (problem strips-gripper-x-5)
   (:domain gripper)
   (:objects
        rooma roomb ball6 ball5 ball4 ball3 ball2 ball1 left right)

   (:init
      (ROOM rooma)
      (ROOM roomb)
      (BALL ball12)
      (BALL ball11)
      (BALL ball10)
      (BALL ball9)
      (BALL ball8)
      (BALL ball7)
      (BALL ball6)
      (BALL ball5)
      (BALL ball4)
      (BALL ball3)
      (BALL ball2)
      (BALL ball1)
      (GRIPPER left)
      (GRIPPER right)
      (at-robby rooma)
      (free left)
      (free right)
      (at-ball ball6 rooma)
      (at-ball ball5 rooma)
      (at-ball ball4 rooma)
      (at-ball ball3 rooma)
      (at-ball ball2 rooma)
      (at-ball ball1 rooma))

   (:goal
       (and
       (at-ball ball6 roomb)
       (at-ball ball5 roomb)
       (at-ball ball4 roomb)
       (at-ball ball3 roomb)
       (at-ball ball2 roomb)
       (at-ball ball1 roomb)))
)