import os

tools = dict()
tools['imei.cc'] = 'imei'

PATH_TO_IB=".."
common = Split(PATH_TO_IB + """/ib/libib.a
	       """)
for i in range(0, 5):
    print ""
print "libib.a set to: " + PATH_TO_IB + "/ib/libib.a"
for i in range(0, 5):
    print ""

libs = Split("""crypto
	     """)
env = Environment(CXX="ccache clang++ -I"+ PATH_TO_IB, CPPFLAGS="-D_FILE_OFFSET_BITS=64 -Wall --std=c++11 -pthread", LIBS=libs, CPPPATH=PATH_TO_IB)
env['ENV']['TERM'] = 'xterm'

Decider('MD5')
for i in tools:
	env.Program(source = [i] + common, target = tools[i])

