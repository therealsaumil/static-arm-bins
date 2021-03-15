static-arm-bins
===============

A collection of statically compiled ARM binaries for debugging and runtime analysis.

-	gdb-arm-static-7.11
-	gdbserver-armel-static-8.0.1
-	ldd-arm-static
-	ltrace-arm-static-0.7.91
-	nc-arm-static
-	nc-armel-static
-	netstat-armel-static
-	ifconfig-armel-static
-	datapipe-armel-static
-	socat-armel-static
-	nohup-armel-static (thanks @shifttymike)
-	dd-armel-static (compiled from coreutils-8.30)
-	id-armel-static (compiled from coreutils-8.30)
-	strace-android-static
-	xxd-armel-static
-	lsof-armel-static
-	telnetd-static (https://github.com/Troll338cz/mini_telnetd)
-	lspci-static
-	setpci-static

Note: This collection of static binaries is provided as-is. Some of them are compiled by me, using the usual CFLAGS/LDFLAGS=-static incantations in the Makefiles; some contributed by friends, and some collected from the world wide web.

@therealsaumil

SHA256:

```
115ad66a444732ea0982c1d5acb334cb4acd706ae195ca7218af2d1d48358ad3  gdb-arm-static-7.11
12415bf9f6da99d7255379fde49af28acc2a73ae486c40103181b70a41b505f9  gdbserver-armel-static-8.0.1
ae30082165cdaddfc6e1a6c6a945062c9227e37e65422951d23517f7293c0143  ldd-arm-static
ce874cc891253d36327f6118984ae315c300cec9b95e6d0545edf39ab8a2afa4  ltrace-arm-static-0.7.91
3b252ac77c79724fec975cc64721f1050afd211fa73e849b39232f703d124720  nc-arm-static
7970beaae99a27ad5a86bf5c58dc8624a5ff13586baac43cf3de4cafb70e2af9  nc-armel-static
c790967c4d06d7b86188f36c15d10281c67e2f4c6c5a28cab192e314435e58a6  netstat-armel-static
7bd7a5a2a1e9eb9edfaadcc0d130e9145dbcdf7b9cc9b42e55ba2c9f7e853edf  ifconfig-armel-static
cde715eea6ec2028015508cd9de083fb98247a55aef176fd035ac287a8c1e907  datapipe-armel-static
4a90f60aedfeb037e0eb51900bbf6e41099a0144af4fb114b7cc025c054a3977  datapipe_arm.c
947d94994555662758c6ad57ec25672e40ce688e135e9b81090d1d58b34392b2  socat-armel-static
b4ce411a404dda84effa7fe4bcc5f045330711fe5436e059ab2370781eb3fb49  nohup-armel-static
52b6b5bceb3db5856166457f2047dd503a4e6aec3bbe50388978029149b6c977  dd-armel-static
50f5e7d7ab83bdb674e013da4c54ad81766a013597de502c43f6fbeb2f00b8f3  id-armel-static
22b8bb65ff649d6a33b4ef9e216c0f7560b52014d6ae5a3817880e1bd6a12bfa  strace-android-static
04b956d9c5c5682623359b5f16accbafe90d513eefc7b54a9962a98f770f2f9e  xxd-armel-static
bca854d2209e2cdd5cb83fdb88d3e66543efdf5890c02eb15f555c5d6290b360  lsof-armel-static
3fc7b82244e1da23f6ada3f270ec7ae76d59f3ec4f5c05e0560206e575283cd1  telnetd-static
995d2acd901b92c0e039f0e168e951e9408c817ffb71fd853c55c811cacbb87d  lspci-static
92baf98acc85b73234fcb776eb034fb2c226252ab6462826c23dd15540ca9a62  setpci-static
```
