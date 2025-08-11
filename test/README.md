declare -x a="   aaaa"
declare -x b="bbbbb  "
declare -x c="cccc"
declare -x d="  dddd   "
declare -x e="eee  eeee   eeee   eeee"
declare -x f="  fff fff fff fff"
declare -x g="ggg ggg ggg ggg    "
declare -x h="  hhh hhh hhh  hhh   "
declare -x i="      "
declare -x j=""
declare -x k=""
declare -x l

## this is in bash


codewithhippo  ~/test  18:09  echo cddsc > $f
bash: $f: ambiguous redirect

codewithhippo  ~/test  18:09  echo cddsc > $g
bash: $g: ambiguous redirect

codewithhippo  ~/test  18:09  echo cddsc > $h
bash: $h: ambiguous redirect

codewithhippo  ~/test  18:09  echo cddsc > $i
bash: $i: ambiguous redirect

codewithhippo  ~/test  18:09  echo cddsc > $j
bash: $j: ambiguous redirect

codewithhippo  ~/test  18:09  echo cddsc > $k
bash: $k: ambiguous redirect

codewithhippo  ~/test  18:09  echo cddsc > $l
bash: $l: ambiguous redirect

codewithhippo  ~/test  18:09  echo cddsc > $m
bash: $m: ambiguous redirect

codewithhippo  ~/test  18:09  export |tail -n 12

################################################

codewithhippo  ~/test  18:12  echo dvsf > abc$a
bash: abc$a: ambiguous redirect

codewithhippo  ~/test  18:13  echo dvsf > abc$b

codewithhippo  ~/test  18:13  echo dvsf > abc$c

codewithhippo  ~/test  18:13  echo dvsf > abc$d
bash: abc$d: ambiguous redirect

codewithhippo  ~/test  18:13  echo dvsf > abc$e
bash: abc$e: ambiguous redirect

codewithhippo  ~/test  18:13  echo dvsf > abc$f
bash: abc$f: ambiguous redirect

codewithhippo  ~/test  18:13  echo dvsf > abc$g
bash: abc$g: ambiguous redirect

codewithhippo  ~/test  18:14  echo dvsf > abc$h
bash: abc$h: ambiguous redirect

codewithhippo  ~/test  18:14  echo dvsf > abc$i

codewithhippo  ~/test  18:14  echo dvsf > abc$j

codewithhippo  ~/test  18:14  echo dvsf > abc$k

codewithhippo  ~/test  18:14  echo dvsf > abc$l

codewithhippo  ~/test  18:14  echo dvsf > abc$m

########################################################

codewithhippo  ~/test  18:16  echo sdcsd > $a#

codewithhippo  ~/test  18:18  echo sdcsd > $b#
bash: $b#: ambiguous redirect

codewithhippo  ~/test  18:18  echo sdcsd > $c#

codewithhippo  ~/test  18:18  echo sdcsd > $d#
bash: $d#: ambiguous redirect

codewithhippo  ~/test  18:18  echo sdcsd > $e#
bash: $e#: ambiguous redirect

codewithhippo  ~/test  18:18  echo sdcsd > $f#
bash: $f#: ambiguous redirect

codewithhippo  ~/test  18:18  echo sdcsd > $g#
bash: $g#: ambiguous redirect

codewithhippo  ~/test  18:18  echo sdcsd > $h#
bash: $h#: ambiguous redirect

codewithhippo  ~/test  18:18  echo sdcsd > $i#

codewithhippo  ~/test  18:18  echo sdcsd > $j#

codewithhippo  ~/test  18:18  echo sdcsd > $k#

codewithhippo  ~/test  18:18  echo sdcsd > $l#

codewithhippo  ~/test  18:18  echo sdcsd > $m#


## and this is in minishell

minishell$ echo cddsc > $a
minishell$ echo cddsc > $b
minishell$ echo cddsc > $c
minishell$ echo cddsc > $d
minishell$ echo cddsc > $e
minishell: : ambiguous redirect
minishell$ echo cddsc > $f
minishell: : ambiguous redirect
minishell$ echo cddsc > $g
minishell: : ambiguous redirect
minishell$ echo cddsc > $h
minishell: : ambiguous redirect
minishell$ echo cddsc > $i
minishell: : ambiguous redirect
minishell$ echo cddsc > $j
minishell: : ambiguous redirect
minishell$ echo cddsc > $k
minishell: : ambiguous redirect
minishell$ echo cddsc > $l
minishell: : ambiguous redirect
minishell$ echo cddsc > $m
minishell: : ambiguous redirect

#########################################

minishell$ echo dvsf > abc$a
minishell: : ambiguous redirect
minishell$ echo dvsf > abc$b
minishell$ echo dvsf > abc$c
minishell$ echo dvsf > abc$d
minishell: : ambiguous redirect
minishell$ echo dvsf > abc$e
minishell: : ambiguous redirect
minishell$ echo dvsf > abc$f
minishell: : ambiguous redirect
minishell$ echo dvsf > abc$g
minishell: : ambiguous redirect
minishell$ echo dvsf > abc$h
minishell: : ambiguous redirect
minishell$ echo dvsf > abc$i
minishell: : ambiguous redirect
minishell$ echo dvsf > abc$j
minishell$ echo dvsf > abc$k
minishell$ echo dvsf > abc$l
minishell$ echo dvsf > abc$m

#########################################

minishell$ echo sdcsd > $a#
minishell$ echo sdcsd > $b#
minishell: : ambiguous redirect
minishell$ echo sdcsd > $c#
minishell$ echo sdcsd > $d#
minishell: : ambiguous redirect
minishell$ echo sdcsd > $e#
minishell: : ambiguous redirect
minishell$ echo sdcsd > $f#
minishell: : ambiguous redirect
minishell$ echo sdcsd > $g#
minishell: : ambiguous redirect
minishell$ echo sdcsd > $h#
minishell: : ambiguous redirect
minishell$ echo sdcsd > $i#
minishell: : ambiguous redirect
minishell$ echo sdcsd > $j#
minishell: : ambiguous redirect
