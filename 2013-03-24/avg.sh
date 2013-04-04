#/bin/bash

for i in ${*}
do
	sum=$((${sum}+$i))
done

#echo $sum
echo $(($sum/${#}))
