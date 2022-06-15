

# export DES_KEY="6162636461626364"
# echo "foo bar" | ./ft_ssl des   -k $DES_KEY |  ./ft_ssl des -d   -k $DES_KEY
# echo "foo bar" | openssl des-ecb -provider legacy -provider default -K $DES_KEY | ./ft_ssl des -d   -k $DES_KEY
# echo "smol" | ./ft_ssl des -k $DES_KEY | openssl des-ecb -provider legacy -provider default -d -K $DES_KEY
# echo "smol" | openssl des-ecb -provider legacy -provider default -K $DES_KEY | ./ft_ssl des -d -k $DES_KEY
# echo "testting the key now" | openssl des-ecb -provider legacy -provider default -K "ABCD" | ./ft_ssl des -d -k "ABCD"
# echo "More key tests" | openssl des-ecb -provider legacy -provider default -K "FFFFFFFFFFFFFFFF" | ./ft_ssl des -d -k "FFFFFFFFFFFFFFFF"
# echo "what kind of lock takes no key?" |  openssl des-ecb -provider legacy -provider default -K "00000000" | ./ft_ssl des -d -k "00000000"

# echo "$(curl 'http://wiki.cs.hse.ru/Программирование_на_С%2B%2B_КНАД')" > original.html
# echo "password" > password_file
# openssl des-ecb -p -provider legacy -provider default -in original.html -out ciphertext.html -pass "pass::$(cat password_file)"
# openssl des-ecb -p -provider legacy -provider default -in password_file -out ciphertext -pass "pass::$(cat password_file)"
# ./ft_ssl des-ecb -d -i ciphertext.html -o decrypted.html -p "$(cat password_file)" -s 99359262080E8DE9
# ./ft_ssl des-ecb -d -i ciphertext -p "$(cat password_file)" -s 99359262080E8DE9

# echo "Make sure they really tell you what is going on 'under the hood' when you use CBC mode, and how it is more secure than ECB" | openssl des-cbc  -provider legacy -provider default -K "BABE101010FACADE" -iv "77696E6B66616365" | ./ft_ssl des-cbc -k "BABE101010FACADE" -v "77696E6B66616365" -d

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

echo "test 6 input  openssl -> base64 -> ft_ssl "
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default -a -e -K 6162636461626364 | ./ft_ssl des -d -a -k 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 7 small input ft_ssl -> base64 -> openssl "
control_phrace="one deep darkk"
result=$(echo $control_phrace |  ./ft_ssl des -e -a -k 6162636461626364 | openssl des-ecb -provider legacy -provider default -a -d -K 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 8 input ft_ssl -> base64 -> openssl "
control_phrace="one deep secret"
result=$(echo $control_phrace |  ./ft_ssl des -e -a -k 6162636461626364 | openssl des-ecb -provider legacy -provider default -a -d -K 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi


echo "test 9 input openssl -> base64 -> ft_ssl"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-ecb -provider legacy -provider default  -e -K 6162636461626364 | ./ft_ssl des -d -k 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi


echo "test 10  input big file ft_ssl-> base64 ->openssl"
openssl rand -hex 2000 > test_big_file
result=$(cat test_big_file | ./ft_ssl des -e -a -k 6162636461626364 | openssl des-ecb -provider legacy -provider default -a -d -K 6162636461626364 )

if echo $result | wc | grep -q "$(cat  test_big_file | wc -c)"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi




echo "test 11 input ft_ssl -> openssl with salt and pass"
control_phrace="one deep secret"
result=$(echo $control_phrace | ./ft_ssl des -e -s 6162636461626364 -p "q" | openssl des-ecb -provider legacy -provider default  -d -S 6162636461626364 -pass pass:q)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 12 input des-cbc openssl -> openssl with key"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-cbc -provider legacy -provider default  -e -K 6162636461626364 -iv 6162636461626364 | openssl des-cbc -provider legacy -provider default  -d -K 6162636461626364 -iv 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 13 input des-cbc openssl -> ft_ssl with key"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-cbc -provider legacy -provider default  -e -K 6162636461626364 -iv 6162636461626364 | ./ft_ssl des-cbc -d -k 6162636461626364 -v 6162636461626364)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi


echo "test 14 input des-cbc ft_ssl  -> openssl with key"
control_phrace="one deep secret"
result=$(echo $control_phrace | ./ft_ssl des-cbc -e -k 6162636461626364 -v 6162636461626364 | openssl des-cbc -provider legacy -provider default  -d -K 6162636461626364 -iv 6162636461626364  )

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi

echo "test 13 input PASS des-cbc openssl -> ft_ssl with key"
control_phrace="one deep secret"
result=$(echo $control_phrace | openssl des-cbc -provider legacy -provider default  -e -pass pass:q | ./ft_ssl des-cbc -d -p q)

if echo $result | grep -q "$control_phrace"; then
	echo "TEST OK"
else
	echo "ERROR"
	exit 0
fi