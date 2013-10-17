import fnmatch
import os

matches = []
for root, dirnames, filenames in os.walk('../src/'):
    for filename in filenames:
        if fnmatch.fnmatch(filename, '*.cpp'):
            matches.append(str(os.path.join(root, filename)))


matches = [m.replace('../', '') for m in matches]

env = Environment()
env.Append(LIBS = ['sfml-audio', 'sfml-graphics','sfml-window','sfml-system'])
env.Append(LIBPATH = '/usr/local/lib')
env.Append(CXXFLAGS = '-std=c++11 -Wall -Wextra -pedantic -Werror')
env.Program(target = 'Dron', source = matches)