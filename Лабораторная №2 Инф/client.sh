#!/bin/bash
echo "Введите сообщение:"
read message
echo $message | nc localhost 9999