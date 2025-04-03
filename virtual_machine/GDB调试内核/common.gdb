

# 计算结构体成员在结构体内偏移量
define offsetof
	print /x (unsigned long)&($arg0->$arg1) - (unsigned long)($arg0)
end

