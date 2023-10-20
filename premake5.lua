-- Solution Details
workspace "A_Pirates_Adventure"
	architecture "x64"
	startproject "Launcher"
	configurations { "Debug", "Release", "Dist" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Engine"
include "Game"
include "Launcher"