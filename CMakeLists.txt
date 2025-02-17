cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MySFMLProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Находим SFML
find_package(SFML REQUIRED COMPONENTS system window graphics audio network)

# Включаем директорию с заголовочными файлами
include_directories(include)

# Собираем список исходных файлов
file(GLOB SOURCES "src/*.cpp")
list(APPEND SOURCES "main.cpp")

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

# Линкуем SFML библиотеки
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
