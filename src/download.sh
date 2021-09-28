zcat ../2020/scc2020*.html.gz | grep 四鳳南喰赤－ | egrep -o 'http.{52}' | sed -e s/"?log="/"log\/?"/g | xargs wget
ls | xargs cat > merged.txt
