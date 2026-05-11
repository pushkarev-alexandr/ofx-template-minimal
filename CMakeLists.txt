cmake_minimum_required(VERSION 3.15)

project(OFXTemplatePlugin)

add_library(OFXTemplatePlugin SHARED src/template.cpp)

target_include_directories(OFXTemplatePlugin PRIVATE include)
