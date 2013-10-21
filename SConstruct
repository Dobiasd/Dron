import fnmatch
import sys
import os


source_files = []
for root, dirnames, filenames in os.walk('src'):
    for filename in filenames:
        if fnmatch.fnmatch(filename, '*.cpp'):
            source_files.append(str(os.path.join(root, filename)))

source_files = [s.replace('src', 'build', 1) for s in source_files]

VariantDir('build', 'src', duplicate=0)

# Windows
if sys.platform[:3] == 'win':
	env = Environment(tools = ['mingw'])

	# Insert your SFML paths here.
	env.Append(CPPPATH='D:\Tobias\Projekte\SFML\SFML-1.6_MinGW\include')
	env.Append(LIBPATH='D:\Tobias\Projekte\SFML\SFML-1.6_MinGW\lib\mingw')


# Linux etc.
else:	
	env = Environment()
	env.Program(target='Dron', source=source_files)


env.Append(LIBS=['sfml-audio', 'sfml-graphics','sfml-window','sfml-system'])
env.Append(CXXFLAGS='-std=c++11 -Wall -Wextra -pedantic -Werror')
env.Program(target='Dron', source=source_files)