
echo "test 1"
control_phrace="one deep secret"
result=$(echo $control_phrace | ./ft_ssl des -e -k 6162636461626364 | openssl des-ecb -provider legacy -provider default  -d -K 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 2"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default  -e -K 6162636461626364 | openssl des-ecb -provider legacy -provider default  -d -K 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 2"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default  -e -K 6162636461626364 | ./ft_ssl des -d -k 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi