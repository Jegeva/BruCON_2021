#! /bin/bash
now=`date '+%Y-%m-%d-%H-%M-%S'`
host=badgesvr.brucon.org

mkdir out 2>/dev/null

openssl genrsa -out out/clicert.key.$now.pem 2048 2>/dev/null

mac=`dd if=/dev/random bs=6 count=1 2>/dev/null|hexdump -e '/1 "%02x:"'|sed 's/.$//'`
cp sk.cnf /tmp/sk.cnf
echo $mac >> /tmp/sk.cnf
openssl req -new -config  /tmp/sk.cnf -key out/clicert.key.$now.pem -keyform PEM -out out/clicert.$now.csr

curl -F CSR=@out/clicert.$now.csr -o out/clicert.$now.pem http://$host/enroll.php



