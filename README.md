# ☕ カフェ管理アプリケーション / CoffeeShop Management Application

## 📌 概要 / Introduction

このアプリケーションは **C++** を用いて開発され、カフェの基本的な運営をサポートすることを目的としています。
This application is developed using **C++**, aiming to support basic coffee shop operations.

対応している役割 / Supported Roles:

* 👨‍💼 **管理者 / Admin**:

  * メニューの閲覧 / View menu
  * 注文管理（注文を登録）/ Manage orders
  * 売上確認 / View revenue
  * 領収書の発行 / Print invoice
  * ※ すべてのデータは `.txt` ファイルに保存されます
  * ※ All related data is stored in `.txt` files

* 👨‍💻 **ユーザー / User**:

  * メニューから注文 / Place orders from the menu

---

## ⚙️ 使用技術 / Technologies Used

* **言語 / Language:** C++
* **データ保存 / Data Storage:** Text files (`.txt`)
* **IDE / 開発環境:** Visual Studio Code / Dev-C++ / g++

---

## 📂 データファイル / Data Files

* `account.txt` : アカウント情報（ユーザー名、パスワード、役割）
  Accounts info (username, password, role)
* `menu.txt` : メニュー情報 / Menu data
* `orders.txt` : 注文履歴 / Order history
* `revenue.txt` : 売上情報 / Revenue data

---

## 🚀 実行方法 / How to Run

### Linux / Mac / MinGW

```bash
g++ src/main.cpp -o coffeehop
./coffeehop
```

### Windows (MSVC)

```bash
cl src\main.cpp /Fe:coffeehop.exe
coffeehop.exe
```

---

## 👥 チーム規模 / Team Size

* **リーダー / Leader:** Đỗ Nguyễn Nam Quân
* **メンバー / Members:** 3–5 名 (3–5 members)

私は **アプリ全体の設計** と **コア機能（ログイン・登録、注文、売上管理）** を担当しました。
I was responsible for **overall system design** and **core features (login/register, ordering, revenue management)**.

---
