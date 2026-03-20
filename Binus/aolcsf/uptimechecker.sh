code=$(curl -L -s -o /dev/null -w "%{http_code}" "$1")

if [ "$code" == "200" ]; then
    echo "$1 is UP"
else
    echo "$1 is DOWN (Status: $code)"
fi
