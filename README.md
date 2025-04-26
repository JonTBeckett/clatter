# clatter

Clatter is the missing tool for handling dependencies for embedded (and more!) software written in C. Modern languages like Go and Rust have all-in-one package managers and build tools (Golang and Cargo respectively). These tools make it incredibly easy to add, identify, and use dependencies in a controlled and unified fashion. There have been a lot of attempts at this type of thing for C, but none seem well suited for the embedded world where sharing pre-compiled binaries or snapshots of the code base aren't always sufficient. Typically source code is compiled with custom user settings from include files and/or command line defines to fine tune the build. Further, all of the source is compiled to object files and then linked together as a final executable in most cases. The intermediate step of linking some object files into a library is bypassed because sharing libraries isn't practical when such extensive configuration is possible. 

Clatter aims at easing the burden of adding and using dependencies in these scenarios. 

## Current Tools
Currently, there are a multitude of build tools that are used by C developers: make, cmake, Visual Studio, Xcode, Keil, IAR, etc. The list goes on and on and varies depending on what kind of tool or application you're developing. Cmake is the closest thing to a standardize way of building that allows extensive expansion and modification but it is not suitable in some scenarios. Some times business needs require the use of another tool chain. Sometimes familiarity forces engineers to stick with what they know.

Engineers are resourceful though, especially engineers that develop software in C (is our bias showing?). They find a way to get the job done. Git submodules have become a common way to maintain simple dependencies that need built directly into the product. This is a great start but it is lacking in a lot of ways. (You may even get ridiculed by certain groups for using them!) Clatter embraces submodules as a way to get to where we want to go. It uses them to setup usable source directories within a repo without requiring the user to manage them directly.

## ????
Submodules don't solve all of the problems though. For one, the consumer still has to manually add its inculde files to their build system's include paths, add the source files to the build system, and manage any number of configuration files. Then, if the submodule needs moved, renamed, or gets a major update that modifies it's directory structure the consumer has to update all of those things again manually! Clatter aims at solving this problem as well. 

Some build tools and IDEs have or will have built in support. These will be the most common such as Cmake, Make, Visual Studio, etc. Beyond the most common, Clatter Extensions will be the solution. The goal is for these to know and understand additional build systems and IDEs like Arm Keil and IAR.


## Design

### Including Dependencies
Clatter provides three ways to include a dependency in your project:

1. Full source in a accessible Git submodule
2. Full source in a hidden Git submodule
3. Libeary binary and include files only as a Git submodule

### Accessible submodules
Accessible submodules can be found in the `clatrdeps` subdirectory. 

### Hidden submodules
Hidden submodules can be found in the `.clatrdeps` subdirectory. 

### Library binaries
Library binaries can be found in the `.clatrlib` subdirectory. 

## Using Dependencies
A file named `clatrconf.yml` can be found in every repository that supports Clatter out of the box. This file has the following strucure:

	name: <name>
	origin: <Git URL or local path>
	version: <version identifier (commit-ish)>
	
	includes: # List of include paths
	    - <path to include files relative to root>

	sources: # List of all source files
		- <path and name of source file>
		- <path to directory>
		- <path and regex>
	    
	dependencies: # List of dependencies
	    <dependency name>:
	        name: <dependency name>
	        origin: <Git URL or local path of dependency>
	        version: <minimum version>
	        relativePath: <Expected relative path> # not required
	       
	artifacts: # artifacts produced by this module
	    <yaml name for artifact:
	        file: <path (relative to root) and name of artifact file>
	        type: <type of artifact> # object/library/executable/binary
	
	extensions:
		<extension name>:
		    # Extension specific structure
		    # Unrecognized extensions are simply ignored