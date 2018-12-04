#! /bin/bash

#explicit host and network values
myHostName=$(hostname)
myIP=$(hostname -i)
CLIENTHOSTS="April Summer Fall June September Equinox December May July Winter March Year Solstice October February August Spring Autumn November January"
NETWORKS="admin net16 net17 net18 net19"
IPV4ADDRESSES="172.16.1.4 172.16.1.13 172.16.1.14 172.16.1.6 172.16.1.9 172.16.1.16 172.16.1.12 172.18.1.12 172.18.1.5 172.18.1.7 172.18.1.15 172.18.1.3 172.19.1.3 172.19.1.18 172.19.1.17 172.19.1.10 172.17.1.2 172.17.1.8 172.17.1.20 172.17.1.11 172.17.1.19 192.168.0.11 172.17.1.1 172.16.1.12"
IPV6ADDRESSES="fdd0:8184:d967:18:250:56ff:fe85:d1d8/64 fdd0:8184:d967:8018:250:56ff:fe85:d1d8/64 fdd0:8184:d967:18:250:56ff:fe85:d1d8 fdd0:8184:d967:8018:250:56ff:fe85:d1d8"

echo Test Reachability of Network Connections of Clients from One Host

echo 

for clienthost in $CLIENTHOSTS
do
    for network in $NETWORKS
    do
        # concat address to check
    	address="$host.$net"
        
        # perform checks, dump std output from ping to dev/null >/dev/null
        #  2>&1 redirect standard error to standard output
        # save output of tracepath and arp to $address
        # if fail output fail
        # print field 3 (ethernet address)
        
	    ping -c 1 "$address" >/dev/null 2>&1
        && echo "$address pass ping test from ${myHostname}"
        && tracepath "$address"
        && arp "$address" | awk '{print $3}' || echo "$address failed from ${myHostname}"
        
	    echo
    done
done

echo Test Reachability of Network Connections of Clients from One Host via IPV4

echo 

for ipv4address in $IPV4
do
	echo $ipv4address
    
    # perform checks, dump std output from ping to dev/null >/dev/null
    #  2>&1 redirect standard error to standard output
    # save output of tracepath and arp to $address
    # if fail output fail
    # print field 3 (ethernet address)
        
	ping -c 1 "$ipv4address" >/dev/null 2>&1 
    && echo "$ipv4address is reachable from ${myIP}" 
    && tracepath "$ipv4address" 
    && arp "$ipv4address" | awk '{print $3}' || echo "$ipv4address is not reachable from ${myIP}"
    
	echo 
done

echo Test Reachability of Network Connections of Clients from One Host via IPV4

echo

for ipv6address in $IPV6
do
	echo $ipv6address
    
    # perform checks, dump std output from ping to dev/null >/dev/null
    #  2>&1 redirect standard error to standard output
    # save output of tracepath and arp to $address
    # if fail output fail
    # print field 3 (ethernet address)
    
	ping6 -c 1 "$ipv6address" >/dev/null 2>&1 
    && echo "$ipv6address is reachable from ${myIP}" 
    && tracepath6 "$ipv6address" 
    && arp "$ipv6address" | awk '{print $3}' || echo "$ipv6address is not reachable from ${myIP}"

	echo
done





