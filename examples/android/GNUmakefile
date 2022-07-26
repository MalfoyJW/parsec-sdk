export ANDROID_HOME = $(HOME)/android-home
export ANDROID_NDK_HOME = $(HOME)/android-ndk-r21e
export ANDROID_SDK_ROOT = $(ANDROID_HOME)/cmdline-tools

all:
	java -classpath gradle/wrapper/gradle-wrapper.jar \
		org.gradle.wrapper.GradleWrapperMain -p . installDebug
