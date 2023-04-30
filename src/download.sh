zcat ../2020/scc2020*.html.gz | grep 四鳳南喰赤－ | grep -E -o 'http.{52}' | sed -e s/"?log="/"log\/?"/g | wget -i - -O - > merged.txt
