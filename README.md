## これは

詳細は下記ふたつのエントリーで紹介しております

- [ycapture で OpenCV での処理結果を Windows のビデオソースとしてブラウザに流し込む](http://izmiz.hateblo.jp/entry/2015/01/12/220133)
- [html から node.js を介して oF の画像処理をコントロールし、ブラウザ上で閲覧する](http://izmiz.hateblo.jp/entry/2015/01/13/224700)

## セットアップ

### 環境

- Windows 7/8.1
- Visual Studio Express 2012
- openFrameworks v0.8.4
	- ofxOsc
	- ofxCv
	- ofxOpenCV (ofxCv 中で呼び出す)

### 手順(1) 連携に使う node.js アプリのセットアップ

[izmhr/browserAndOF](https://github.com/izmhr/browserAndOF)

上記リポジトリの README にしたがってセットアップして下さい

### 手順(2) 本プロジェクトのビルド・セットアップ

#### 本リポジトリをClone

`<OF_ROOT>\apps\myApps\browserAndCV2` の位置に、本プロジェクトを配置します

#### ofxCv アドオンを準備

`<OF_ROOT>\addons\ofxCv` の位置に ofxCv を置きます

[kylemcdonald/ofxCv](https://github.com/kylemcdonald/ofxCv)

#### ycapture の導入

下記2記事を参考にしてください

- [ycapture(わいきゃぷちゃ) 公式](http://yzwlab.net/ycapture/)
- [ycapture で OpenCV での処理結果を Windows のビデオソースとしてブラウザに流し込む](http://izmiz.hateblo.jp/entry/2015/01/12/220133)

#### OSCポートの設定

手順(1) で node.js に対して行ったポート設定とあわせてください。 `ofApp.h` 9行目で `#define` しています。

#### ビルド & ラン
