

echo "test 1 input ft_ssl -> openssl with key"
control_phrace="one deep secret"
result=$(echo $control_phrace | ./ft_ssl des -e -k 6162636461626364 | openssl des-ecb -provider legacy -provider default  -d -K 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 2 input opensl -> openssl"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default  -e -K 6162636461626364 | openssl des-ecb -provider legacy -provider default  -d -K 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 3 input openssl -> ft_ssl with key"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default  -e -K 6162636461626364 | ./ft_ssl des -d -k 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi


echo "test 4  input big file openssl->ft_ssl"
openssl rand -hex 2000 > test_big_file
result=$(cat test_big_file | openssl des-ecb -provider legacy -provider default  -e -K 6162636461626364 | ./ft_ssl des -d -k 6162636461626364)

if echo $result | wc | grep -q "$(cat  test_big_file | wc -c)"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi


echo "test 5 input   openssl -> base64 -> openssl"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default -a -e -K 6162636461626364 | openssl des-ecb -provider legacy -provider default -a -d -K 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 5 input  openssl -> base64 -> ft_ssl "
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default -a -e -K 6162636461626364 | ./ft_ssl des -d -a -k 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 6 small input ft_ssl -> base64 -> openssl "
control_phrace="one deep darkk"
result=$(echo $control_phrace |  ./ft_ssl des -e -a -k 6162636461626364 | openssl des-ecb -provider legacy -provider default -a -d -K 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 5 input ft_ssl -> base64 -> openssl "
control_phrace="one deep secret"
result=$(echo $control_phrace |  ./ft_ssl des -e -a -k 6162636461626364 | openssl des-ecb -provider legacy -provider default -a -d -K 6162636461626364)
echo $result
if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi


echo "test 6 input openssl -> base64 -> ft_ssl"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default  -e -K 6162636461626364 | ./ft_ssl des -d -k 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi


echo "test 7  input big file ft_ssl-> base64 ->openssl"
openssl rand -hex 2000 > test_big_file
result=$(cat test_big_file | ./ft_ssl des -e -a -k 6162636461626364 | openssl des-ecb -provider legacy -provider default -a -e -K 6162636461626364 )

if echo $result | wc | grep -q "$(cat  test_big_file | wc -c)"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi
