#!/bin/bash

# Путь к директории с исходными файлами
SRC_DIR="src"

cd "$SRC_DIR"
# Перебираем каждую поддиректорию в директории SRC_DIR
find . -type d | while read -r dir; do
    # Проверяем, есть ли в директории хотя бы один .cpp или .h файл
    if ls "$dir"/*.cpp "$dir"/*.h >/dev/null 2>&1; then
        cd "$dir"
        # Создаём (или перезаписываем) CMakeLists.txt в текущей директории
        CMAKE_FILE="CMakeLists.txt"
        echo "" > "$CMAKE_FILE"
        
        # Записываем файлы .cpp в секцию SOURCES
        echo "set(SOURCES" >> "$CMAKE_FILE"
        find . -maxdepth 1 -type f -name "*.cpp" | while read -r file; do
            echo "    $file" >> "$CMAKE_FILE"
        done
        echo ")" >> "$CMAKE_FILE"
        echo "" >> "$CMAKE_FILE"
        
        # Записываем файлы .h в секцию HEADERS
        echo "set(HEADERS" >> "$CMAKE_FILE"
        find . -maxdepth 1 -type f -name "*.h" | while read -r file; do
            echo "    $file" >> "$CMAKE_FILE"
        done
        echo ")" >> "$CMAKE_FILE"
        echo "" >> "$CMAKE_FILE"

        # Добавляем строки для target_sources и target_include_directories
        cat <<EOL >> "$CMAKE_FILE"
target_sources(\${PROJECT_NAME} PRIVATE \${SOURCES} \${HEADERS})
target_include_directories(\${PROJECT_NAME} PUBLIC \$<BUILD_INTERFACE:\${CMAKE_CURRENT_LIST_DIR}>)
EOL

        # Сообщение о создании CMakeLists.txt
        echo "CMakeLists.txt создан в директории $dir"
        cd ..
    fi
done