# 🎵 pipewire


<div align="center">

[![Platform](https://img.shields.io/badge/platform-Linux-blue?logo=linux&logoColor=white)](https://www.linux.org/)
[![Language](https://img.shields.io/badge/language-C%2B%2B17-00599C?logo=c%2B%2B)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![Release](https://img.shields.io/badge/release-v1.0.0-brightgreen)](https://github.com/vk-candpython/pipewire/releases/tag/v1.0.0)

*Professional low‑latency and high‑quality audio configuration for PipeWire*

</div>

---

## 📖 Table of Contents | Оглавление

- [English](#english)
  - [📋 Overview](#-overview)
  - [✨ Features](#-features)
  - [⚙️ Configuration Details](#️-configuration-details)
  - [🚀 Quick Start](#-quick-start)
  - [🛠️ Building from Source](#️-building-from-source)
  - [📁 Generated Files](#-generated-files)
  - [🔧 Troubleshooting](#-troubleshooting)

- [Русский](#русский)
  - [📋 Обзор](#-обзор)
  - [✨ Возможности](#-возможности)
  - [⚙️ Детали конфигурации](#️-детали-конфигурации)
  - [🚀 Быстрый старт](#-быстрый-старт)
  - [🛠️ Сборка из исходников](#️-сборка-из-исходников)
  - [📁 Создаваемые файлы](#-создаваемые-файлы)
  - [🔧 Устранение неполадок](#-устранение-неполадок)

---

# English

## 📋 Overview

**PipeWire Setup Utility** — is a lightweight C++ tool that automatically configures PipeWire for **extreme low‑latency and maximum audio quality** on Linux.

It creates optimized configuration files for:

- 🎧 Music production (DAWs, JACK applications)
- 🎮 Gaming with minimal audio delay
- 🎬 Content creation and streaming
- 🖥️ General desktop audio enhancement

> 🔥 The utility applies a **fixed 48 kHz sample rate**, **256 samples buffer size (~5.3 ms latency)**, **S32LE format**, **resample quality 15**, and **Shibata dithering** — delivering studio‑grade audio with ultra‑low latency.

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🧠 **Zero‑Config** | Just run the binary — everything is set up automatically |
| 🔒 **User‑Scoped** | Installs configuration to `~/.config/pipewire/` — no `sudo` required |
| ✅ **Safety Checks** | Verifies PipeWire installation and OS compatibility |
| ⚡ **Ultra‑Low Latency** | Fixed 48 kHz / 256 samples (~5.3 ms) |
| 🎛️ **Maximum Quality** | 32‑bit integer format, resample quality 15, Shibata dithering |
| 🔄 **Service Restart** | Automatically restarts PipeWire services after setup |
| 🧹 **Clean Output** | Clear console feedback showing which files were written |

## ⚙️ Configuration Details

### 🎚️ Audio Pipeline Parameters

| Parameter | Value | Rationale |
|-----------|-------|-----------|
| **Sample Rate** | `48000 Hz` | Industry standard for professional audio |
| **Buffer Size** | `256 samples` | Low latency (~5.3 ms) without risking xruns |
| **Audio Format** | `S32LE` | 32‑bit signed integer — preserves dynamic range |
| **Dithering** | `shibata` | Minimizes quantization noise at low levels |
| **Resample Quality** | `15` (maximum) | Best possible quality for sample rate conversion |

### 📦 Included Configuration Files

| File | Purpose |
|------|---------|
| `pipewire.conf` | Main daemon configuration with ALSA device definitions |
| `pipewire-pulse.conf` | PulseAudio compatibility layer |
| `client.conf` | Standard client settings |
| `client-rt.conf` | Real‑time client configuration |
| `jack.conf` | JACK API compatibility |

Each file is pre‑tuned for **ultra‑low latency and maximum fidelity**.

## 🚀 Quick Start

### 📥 Download Pre‑built Binary

```bash
wget https://github.com/vk-candpython/pipewire/releases/download/v1.0.0/pipewire-setup
chmod +x pipewire-setup
./pipewire-setup
```

**Expected output:**
```
Starting setup PipeWire for current USER(/home/username) [*]
/home/username/.config/pipewire/pipewire.conf [+]
/home/username/.config/pipewire/pipewire-pulse.conf [+]
/home/username/.config/pipewire/client.conf [+]
/home/username/.config/pipewire/client-rt.conf [+]
/home/username/.config/pipewire/jack.conf [+]
Setuped PipeWire for current USER [+]
```

### 🔄 After Setup

Restart your audio applications or log out and back in. Or run:
```bash
systemctl --user restart pipewire.service pipewire-pulse.service wireplumber.service
```

## 🛠️ Building from Source

### Prerequisites

- Compiler (`g++` or `clang++`)
- PipeWire installed

### Build

```bash
g++ -Os -s -o pipewire-setup setup.cpp
```

No external dependencies.

## 📁 Generated Files

```
~/.config/pipewire/
├── pipewire.conf
├── pipewire-pulse.conf
├── client.conf
├── client-rt.conf
└── jack.conf
```

> ⚠️ Existing files will be overwritten. Back up your current PipeWire config if needed.

## 🔧 Troubleshooting

| Issue | Solution |
|-------|----------|
| `Cannot determine HOME directory` | `$HOME` is unset. Run: `export HOME=/home/yourname` |
| `PipeWire not installed` | Install: `sudo apt install pipewire pipewire-pulse wireplumber` |
| `Failed restarting services` | Restart manually: `systemctl --user restart pipewire.service pipewire-pulse.service wireplumber.service` |
| Audio crackles at 256 samples | Increase `api.alsa.period-size` to 256 and `headroom` to 512 in `pipewire.conf` |

---

# Русский

## 📋 Обзор

**PipeWire Setup Utility** — лёгкая C++ утилита, которая автоматически настраивает PipeWire для **предельно низкой задержки и максимального качества звука** на Linux.

Создаёт оптимизированные конфигурационные файлы для:

- 🎧 Создания музыки (DAW, JACK‑приложения)
- 🎮 Игр с минимальной задержкой звука
- 🎬 Создания контента и стримов
- 🖥️ Повседневного использования с студийным качеством

> 🔥 Утилита фиксирует **48 кГц**, **буфер 256 семплов (~5.3 мс)**, **формат S32LE**, **качество ресемплинга 15** и **дизеринг Shibata** — студийный звук с ультра‑низкой задержкой.

## ✨ Возможности

| Возможность | Описание |
|-------------|----------|
| 🧠 **Без настройки** | Просто запусти бинарник — всё настраивается автоматически |
| 🔒 **Пользовательский уровень** | Конфиги кладутся в `~/.config/pipewire/` — без `sudo` |
| ✅ **Проверки** | Проверка установки PipeWire и совместимости с ОС |
| ⚡ **Ультра‑низкая задержка** | 48 кГц / 256 семплов (~5.3 мс) |
| 🎛️ **Максимальное качество** | 32‑битный целый формат, ресемплинг 15, дизеринг Shibata |
| 🔄 **Перезапуск сервисов** | Автоматический перезапуск PipeWire после настройки |
| 🧹 **Чистый вывод** | Понятный отчёт в консоли, какие файлы записаны |

## ⚙️ Детали конфигурации

### 🎚️ Параметры звукового тракта

| Параметр | Значение | Обоснование |
|----------|----------|-------------|
| **Частота дискретизации** | `48000 Гц` | Индустриальный стандарт для профессионального аудио |
| **Размер буфера** | `256 семплов` | Низкая задержка (~5.3 мс) без риска xrun‑ов |
| **Аудиоформат** | `S32LE` | 32‑битное знаковое целое — сохраняет динамический диапазон |
| **Дизеринг** | `shibata` | Минимизирует шум квантования на низких уровнях |
| **Качество ресемплинга** | `15` (максимум) | Наивысшее качество при преобразовании частоты |

### 📦 Создаваемые конфигурационные файлы

| Файл | Назначение |
|------|------------|
| `pipewire.conf` | Основная конфигурация демона с ALSA‑устройствами |
| `pipewire-pulse.conf` | Слой совместимости с PulseAudio |
| `client.conf` | Стандартные настройки клиента |
| `client-rt.conf` | Настройки клиента реального времени |
| `jack.conf` | Совместимость с JACK API |

Каждый файл уже настроен на **ультра‑низкую задержку и максимальное качество**.

## 🚀 Быстрый старт

### 📥 Скачать готовый бинарник

```bash
wget https://github.com/vk-candpython/pipewire/releases/download/v1.0.0/pipewire-setup
chmod +x pipewire-setup
./pipewire-setup
```

**Ожидаемый вывод:**
```
Starting setup PipeWire for current USER(/home/username) [*]
/home/username/.config/pipewire/pipewire.conf [+]
/home/username/.config/pipewire/pipewire-pulse.conf [+]
/home/username/.config/pipewire/client.conf [+]
/home/username/.config/pipewire/client-rt.conf [+]
/home/username/.config/pipewire/jack.conf [+]
Setuped PipeWire for current USER [+]
```

### 🔄 После настройки

Перезапусти свои аудио‑приложения или выйди и зайди обратно в систему. Либо выполни:
```bash
systemctl --user restart pipewire.service pipewire-pulse.service wireplumber.service
```

## 🛠️ Сборка из исходников

### Зависимости

- Компилятор (`g++` или `clang++`)
- Установленный PipeWire

### Сборка

```bash
g++ -Os -s -o pipewire-setup setup.cpp
```

Никаких внешних зависимостей.

## 📁 Создаваемые файлы

```
~/.config/pipewire/
├── pipewire.conf
├── pipewire-pulse.conf
├── client.conf
├── client-rt.conf
└── jack.conf
```

> ⚠️ Существующие файлы будут перезаписаны. Сделай резервную копию текущей конфигурации, если это нужно.

## 🔧 Устранение неполадок

| Проблема | Решение |
|----------|---------|
| `Cannot determine HOME directory` | Переменная `$HOME` не задана. Выполни: `export HOME=/home/твоё_имя` |
| `PipeWire not installed` | Установи: `sudo apt install pipewire pipewire-pulse wireplumber` |
| `Failed restarting services` | Перезапусти вручную: `systemctl --user restart pipewire.service pipewire-pulse.service wireplumber.service` |
| Щелчки / xruns при 256 семплах | Увеличь `api.alsa.period-size` до 256 и `headroom` до 512 в `pipewire.conf` |

---

<div align="center">

**[⬆ Back to Top](#-pipewire)**

*Made for the Linux Audio Community*

</div>
