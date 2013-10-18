import fnmatch
import os

source_files = []
for root, dirnames, filenames in os.walk('src'):
    for filename in filenames:
        if fnmatch.fnmatch(filename, '*.cpp'):
            source_files.append(str(os.path.join(root, filename)))

source_files = [s.replace('src/', 'build/', 1) for s in source_files]

VariantDir('build', 'src', duplicate=0)
env = Environment()
env.Append(LIBS=['sfml-audio', 'sfml-graphics','sfml-window','sfml-system'])
env.Append(LIBPATH='/usr/local/lib')
env.Append(CXXFLAGS='-std=c++11 -Wall -Wextra -pedantic -Werror')
env.Program(target='Dron', source=source_files)