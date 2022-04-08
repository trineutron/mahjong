# mahjong
麻雀研究

## ディレクトリ構成
- [src](src): ソースコード
  - [src/1player](src/1player): 他家の思考を無視した場合の和了率
    - ronはロンを含む
    - pengはポン・ロンを含む
- [data](data): 対応するソースコードから得られたデータ

## 麻雀研究を始めたい人のために
### 天鳳牌譜のダウンロード
mjlogファイル (XML風の形式) を自分でパースする方針です。[麻雀にどんよくです:天鳳牌譜解析をはじめたい人へ](http://blog.livedoor.jp/taj_mahal/archives/52075199.html)も参考にしてください。

1. [天鳳ログ](http://tenhou.net/sc/raw/)の「過去ログ」からダウンロードしたい年のリンクをクリックし、ダウンロードします。
2. 牌譜を置きたいディレクトリを作成します。
3. 2.の親ディレクトリにダウンロードしたzipファイルを展開します。
4. （2020年の4人打ち以外を対象とする場合）[src/download.sh](src/download.sh)を編集します。
5. 2.のディレクトリで[src/download.sh](src/download.sh)を実行します。
6. [src/parse.cpp](src/parse.cpp)を利用し、1行に1タグが対応するようにします。現時点では標準入出力を使用しているのでリダイレクトを活用してください。

### mjlogファイルについて
XML風の形式です。詳しくは[天鳳の牌譜形式を解析する(1) - koba::blog](https://blog.kobalab.net/entry/20170225/1488036549)を参照してください。

## ライセンス
本プロジェクトはMIT Licenseでライセンスされています。詳しくは[LICENSE](LICENSE)をお読みください。
