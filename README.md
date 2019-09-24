目录结构说明
TMSC-Agent
	|
	+- conf snmpd和snmptrapd的配置文件
	|
	+- doc 开发相关文档
	|
	+- mibs 扩展代理的自定义MIB文件
	|
	+- net-snmp-5.7.2.1
	|	|
	|	+- agent/mibgroup/hzchangrong-tmcs-mib 扩展代理的自定义MIB文件对应的实现代码
	|
	+- thirdparty 
		|
		+- 0001-CHANGES-BUG-2712-Fix-Perl-module-compilation.patch ubuntu下编译错误补丁
		|
		+- 0001-Remove-U64-typedef.patch ubuntu下编译错误补丁
		|
		+- strawberry-perl-5.30.0.1-32bit.msi win32下的perl
		|
		+- Win32OpenSSL-1_0_2t.exe win32下的openssl
