#! /bin/bash

# Questions:
# 1. Will you be deploying this code into a client host (Example: August)?
# 2. To test the reachabilty for IPv4 do I use the 192 or 172 IP address?

HOSTS="April Summer Fall June September Equinox December May July Winter March Year Solstice October February August Spring Autumn November January"
NETS="admin net16 net17 net18 net19"

IPV4="172.16.1.4 172.16.1.13 172.16.1.14 172.16.1.6 172.16.1.9 172.16.1.16 172.16.1.12 172.18.1.12 172.18.1.5 172.18.1.7 172.18.1.15 172.18.1.3 172.19.1.3 172.19.1.18 172.19.1.17 172.19.1.10 172.17.1.2 172.17.1.8 172.17.1.20 172.17.1.11 172.17.1.19 192.168.0.11 172.17.1.1 172.16.1.12"
IPV6="fdd0:8184:d967:18:250:56ff:fe85:d1d8/64 fdd0:8184:d967:8018:250:56ff:fe85:d1d8/64 fdd0:8184:d967:18:250:56ff:fe85:d1d8 fdd0:8184:d967:8018:250:56ff:fe85:d1d8"

myHostname=$(hostname)
myIPAddress=$(hostname -i)

echo Reachability to Hostname Destination
echo 
for host in $HOSTS 
do

    # Return tracepath and Ethernet Mac Address if successful

    for net in $NETS
    do
    	address="$host.$net"
	    ping -c 1 "$address" >/dev/null 2>&1 && echo "$address is reachable from ${myHostname}" && tracepath "$address" && arp "$address" | awk '{print $3}' || echo "$address is not reachable from ${myHostname}"
	    echo
    done
done

echo Reachability to IPv4 address
echo 

for address in $IPV4
do
	echo $address
	ping -c 1 "$address" >/dev/null 2>&1 && echo "$address is reachable from ${myIPAddress}" && tracepath "$address" && arp "$address" | awk '{print $3}' || echo "$address is not reachable from ${myIPAddress}"
	echo 
done

echo Reachability to IPv6 address
echo 

for ip6 in $IPV6
do
	echo $ip6
	ping6 -c 1 "$ip6" >/dev/null 2>&1 && echo "$ip6 is reachable from ${myHostname}" && tracepath6 "$ip6" && arp "$ip6" | awk '{print $3}' || echo "$ip6 is not reachable from ${myHostname}"
	echo
	ping6 -c 1 "$ip6" >/dev/null 2>&1 && echo "$ip6 is reachable from ${myIPAddress}" && tracepath6 "$ip6" && arp "$ip6" | awk '{print $3}' || echo "$ip6 is not reachable from ${myIPAddress}"
	echo
done





