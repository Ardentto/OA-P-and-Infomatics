#!/bin/bash
echo "Сервер запущен на порту 9999"
while true; do
    echo "Сообщение получено" | nc -l -p 9999
done