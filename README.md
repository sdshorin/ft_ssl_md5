# ft_ssl_md5

### Hashes: md5 sha256 sha224 sha512 sha384 sha512/256

### Enconding/Decoding base64, des

Project from 42 School: https://en.wikipedia.org/wiki/42_(school)

Subject: hash https://github.com/fpetras/42-subjects/blob/master/ft_ssl_md5.en.pdf/

Subject: base64, des https://github.com/fpetras/42-subjects/blob/master/ft_ssl_des.en.pdf/



## Compilation:
 ```
 make
 ```
 
 ## Run 
```
./ft_ssl command [command opts] [command args]
```
# Examples: 

### HASH
__________________
- -q, quet mode
- -s, hash from string

```
> ./ft_ssl md5 file.txt
MD5 (file.txt) = ca2df19397125e25c55ce165cb209c59 # md5 hash of file
```

```
> ./ft_ssl sha384  file.txt
SHA384 (file.txt) = 7d17e90b83269decaf0564095bd733243f3caa74ff035cbb9157e3bdec49b014d93bb8bd43d36e12826f656ba6e9b099 # sha384 hash of file
```

```
> ./ft_ssl sha512 -q -s "The quick brown fox jumps over the lazy dog"
07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb642e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6
```

### BASE64
__________________

- -d, decode mode
- -e, encode mode (default) 
- -i, input file
- -o, output file

```
> echo "The quick brown fox jumps over the lazy dog"  | ./ft_ssl base64 -e
VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZwo=
```

```
>echo VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZwo= | ./ft_ssl base64 -d
The quick brown fox jumps over the lazy dog
```

```
>./ft_ssl base64 -e -i ./ft_ssl > ft_ssl.base64
```

### DES (in devepment)
____________________
wiki link: https://en.wikipedia.org/wiki/Data_Encryption_Standard/

```
> echo "one deep secret" | ./ft_ssl des-cbc -a -k 6162636461626364 -v 0011223344556677
zqYWONX68rWNxl7msIdGC67Uh2HfVEBo
```

```
> echo "zqYWONX68rWNxl7msIdGC67Uh2HfVEBo" | openssl des-cbc -d -a -K 6162636461626364 -iv 0011223344556677
one deep secret
```







