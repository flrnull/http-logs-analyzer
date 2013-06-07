# Environment 
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_CONF=Release
CND_CONF_DEBUG=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}
OBJECTDEBUGDIR=${CND_BUILDDIR}/${CND_CONF_DEBUG}

# Release object Files
OBJECTFILES= \
	${OBJECTDIR}/Config.o \
	${OBJECTDIR}/Debug.o \
	${OBJECTDIR}/Parser.o \
	${OBJECTDIR}/Result.o \
	${OBJECTDIR}/main.o
	
# Debug object Files	
OBJECTDEBUGFILES= \
	${OBJECTDEBUGDIR}/Config.o \
	${OBJECTDEBUGDIR}/Debug.o \
	${OBJECTDEBUGDIR}/Parser.o \
	${OBJECTDEBUGDIR}/Result.o \
	${OBJECTDEBUGDIR}/main.o

# Release build
${CND_DISTDIR}/${CND_CONF}/http-logs-analyzer.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/http-logs-analyzer ${OBJECTFILES}

# Debug build
${CND_DISTDIR}/${CND_CONF_DEBUG}/http-logs-analyzer.exe: ${OBJECTDEBUGFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF_DEBUG}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF_DEBUG}/http-logs-analyzer ${OBJECTDEBUGFILES}

# Release objects
${OBJECTDIR}/Config.o: Config.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Config.o Config.cpp

${OBJECTDIR}/Debug.o: Debug.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Debug.o Debug.cpp

${OBJECTDIR}/Parser.o: Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Parser.o Parser.cpp

${OBJECTDIR}/Result.o: Result.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Result.o Result.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Debug objects
${OBJECTDEBUGDIR}/Config.o: Config.cpp 
	${MKDIR} -p ${OBJECTDEBUGDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDEBUGDIR}/Config.o Config.cpp

${OBJECTDEBUGDIR}/Debug.o: Debug.cpp 
	${MKDIR} -p ${OBJECTDEBUGDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDEBUGDIR}/Debug.o Debug.cpp

${OBJECTDEBUGDIR}/Parser.o: Parser.cpp 
	${MKDIR} -p ${OBJECTDEBUGDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDEBUGDIR}/Parser.o Parser.cpp

${OBJECTDEBUGDIR}/Result.o: Result.cpp 
	${MKDIR} -p ${OBJECTDEBUGDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDEBUGDIR}/Result.o Result.cpp

${OBJECTDEBUGDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDEBUGDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDEBUGDIR}/main.o main.cpp


debug: clean ${CND_DISTDIR}/${CND_CONF_DEBUG}/http-logs-analyzer.exe
	
clean:
	rm -rf build dist