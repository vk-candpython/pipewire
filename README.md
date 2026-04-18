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

**PipeWire Setup Utility** is a lightweight C++ tool that automatically configures PipeWire for **professional low‑latency and high‑quality audio** on Linux.

It creates optimized configuration files tailored for:

- 🎧 Music production (DAWs, JACK applications)
- 🎮 Gaming with minimal audio delay
- 🎬 Content creation and streaming
- 🖥️ General desktop audio enhancement

> 🔥 The utility applies a **fixed 48 kHz sample rate**, **512 samples buffer size**, **S32LE format**, and **Shibata dithering** — a combination that delivers **studio‑grade audio quality** with minimal CPU overhead.

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🧠 **Zero‑Config** | Just run the binary — everything is set up automatically |
| 🔒 **User‑Scoped** | Installs configuration to `~/.config/pipewire/` — no `sudo` required |
| ✅ **Safety Checks** | Verifies PipeWire installation and OS compatibility |
| ⚡ **Low Latency** | Fixed 48 kHz / 512 samples (~10.6 ms latency) |
| 🎛️ **High Quality** | 32‑bit integer format + Shibata dithering |
| 🔄 **Service Restart** | Automatically restarts PipeWire services after setup |
| 🧹 **Clean Output** | Clear console feedback showing which files were written |

## ⚙️ Configuration Details

### 🎚️ Audio Pipeline Parameters

| Parameter | Value | Rationale |
|-----------|-------|-----------|
| **Sample Rate** | `48000 Hz` | Industry standard for professional audio |
| **Buffer Size** | `512 samples` | Low latency (~10.6 ms) without risking xruns |
| **Audio Format** | `S32LE` | 32‑bit signed integer — preserves dynamic range |
| **Dithering** | `shibata` | Minimizes quantization noise at low levels |
| **Resample Quality** | `10` (maximum) | Best possible quality for sample rate conversion |

### 📦 Included Configuration Files

| File | Purpose |
|------|---------|
| `pipewire.conf` | Main daemon configuration with ALSA device definitions |
| `pipewire-pulse.conf` | PulseAudio compatibility layer |
| `client.conf` | Standard client settings |
| `client-rt.conf` | Real‑time client configuration |
| `jack.conf` | JACK API compatibility |

Each file is pre‑tuned for **low‑latency and high‑quality performance** while maintaining stability.

## 🚀 Quick Start

### 📥 Download Pre‑built Binary

Download the latest release from the [Releases Page](https://github.com/vk-candpython/pipewire/releases/tag/v1.0.0):

```bash
wget https://github.com/vk-candpython/pipewire/releases/download/v1.0.0/pipewire-setup
chmod +x pipewire-setup
./pipewire-setup
```

### 🏃 Run

```bash
./pipewire-setup
```

**Expected output:**
```
Start setuping PipeWire for current USER [*]
/home/username/.config/pipewire/pipewire.conf [+]
/home/username/.config/pipewire/pipewire-pulse.conf [+]
/home/username/.config/pipewire/client.conf [+]
/home/username/.config/pipewire/client-rt.conf [+]
/home/username/.config/pipewire/jack.conf [+]
Setuped PipeWire for current USER [+]
```

### 🔄 After Setup

Restart your audio applications or simply **log out and back in** for changes to take full effect.

## 🛠️ Building from Source

### Prerequisites

- **C++17** compatible compiler (`g++` or `clang++`)
- PipeWire installed on the system

### Build

```bash
g++ -std=c++17 -Os -o pipewire-setup setup.cpp
```

That's it. No external dependencies required.

## 📁 Generated Files

All configuration files are placed in:

```
~/.config/pipewire/
├── pipewire.conf          # Main daemon configuration
├── pipewire-pulse.conf    # PulseAudio bridge
├── client.conf            # Default client settings
├── client-rt.conf         # Real‑time client settings
└── jack.conf              # JACK compatibility layer
```

> ⚠️ **Note:** Existing configuration files will be **overwritten**. Consider backing up your current PipeWire config if you have custom modifications.

## 🔧 Troubleshooting

| Issue | Solution |
|-------|----------|
| `Cannot determine HOME directory` | Your `$HOME` environment variable is unset. Run: `export HOME=/home/yourname` |
| `DO NOT SUPPORT OS` | The `~/.config` directory is missing. This tool is designed for standard Linux environments. |
| `PipeWire not installed` | Install PipeWire first: `sudo apt install pipewire pipewire-pulse wireplumber` |
| `Failed restarting PipeWire services` | Manually restart: `systemctl --user restart pipewire.service pipewire-pulse.service wireplumber.service` |
| Audio still has high latency | Ensure no other audio servers (PulseAudio, JACK) are running and conflicting. |

---

# Русский

## 📋 Обзор

**PipeWire Setup Utility** — это легковесная утилита на C++, которая автоматически настраивает PipeWire для **профессионального аудио с низкой задержкой и высоким качеством** на Linux.

Она создаёт оптимизированные конфигурационные файлы, подходящие для:

- 🎧 Создания музыки (DAW, JACK‑приложения)
- 🎮 Игр с минимальной задержкой звука
- 🎬 Создания контента и стриминга
- 🖥️ Улучшения обычного звука рабочего стола

> 🔥 Утилита применяет **фиксированную частоту 48 кГц**, **размер буфера 512 семплов**, **формат S32LE** и **дизеринг Shibata** — комбинацию, обеспечивающую **студийное качество звука** с минимальной нагрузкой на процессор.

## ✨ Возможности

| Возможность | Описание |
|-------------|----------|
| 🧠 **Без настройки** | Просто запусти бинарник — всё настраивается автоматически |
| 🔒 **На уровне пользователя** | Устанавливает конфигурацию в `~/.config/pipewire/` — `sudo` не требуется |
| ✅ **Проверки безопасности** | Проверяет наличие PipeWire и совместимость с ОС |
| ⚡ **Низкая задержка** | Фиксированные 48 кГц / 512 семплов (~10.6 мс задержки) |
| 🎛️ **Высокое качество** | 32‑битный целочисленный формат + дизеринг Shibata |
| 🔄 **Перезапуск служб** | Автоматически перезапускает службы PipeWire после настройки |
| 🧹 **Чистый вывод** | Понятный консольный вывод с указанием записанных файлов |

## ⚙️ Детали конфигурации

### 🎚️ Параметры аудио-тракта

| Параметр | Значение | Обоснование |
|----------|----------|-------------|
| **Частота дискретизации** | `48000 Гц` | Индустриальный стандарт для профессионального аудио |
| **Размер буфера** | `512 семплов` | Низкая задержка (~10.6 мс) без риска xrun‑ов |
| **Аудио формат** | `S32LE` | 32‑битное знаковое целое — сохраняет динамический диапазон |
| **Дизеринг** | `shibata` | Минимизирует шум квантования на низких уровнях |
| **Качество ресемплинга** | `10` (максимум) | Наилучшее качество при преобразовании частоты |

### 📦 Включённые конфигурационные файлы

| Файл | Назначение |
|------|------------|
| `pipewire.conf` | Основная конфигурация демона с определениями ALSA‑устройств |
| `pipewire-pulse.conf` | Слой совместимости с PulseAudio |
| `client.conf` | Стандартные настройки клиента |
| `client-rt.conf` | Конфигурация для клиентов реального времени |
| `jack.conf` | Совместимость с JACK API |

Каждый файл предварительно настроен на **низкую задержку и высокое качество** с сохранением стабильности.

## 🚀 Быстрый старт

### 📥 Скачать готовый бинарник

Скачай последний релиз со [страницы релизов](https://github.com/vk-candpython/pipewire/releases/tag/v1.0.0):

```bash
wget https://github.com/vk-candpython/pipewire/releases/download/v1.0.0/pipewire-setup
chmod +x pipewire-setup
./pipewire-setup
```

### 🏃 Запуск

```bash
./pipewire-setup
```

**Ожидаемый вывод:**
```
Start setuping PipeWire for current USER [*]
/home/username/.config/pipewire/pipewire.conf [+]
/home/username/.config/pipewire/pipewire-pulse.conf [+]
/home/username/.config/pipewire/client.conf [+]
/home/username/.config/pipewire/client-rt.conf [+]
/home/username/.config/pipewire/jack.conf [+]
Setuped PipeWire for current USER [+]
```

### 🔄 После настройки

Перезапусти свои аудио‑приложения или просто **выйди и зайди обратно** в систему для полного применения изменений.

## 🛠️ Сборка из исходников

### Зависимости

- Компилятор с поддержкой **C++17** (`g++` или `clang++`)
- Установленный PipeWire

### Сборка

```bash
g++ -std=c++17 -Os -o pipewire-setup setup.cpp
```

Всё. Никаких внешних зависимостей не требуется.

## 📁 Создаваемые файлы

Все файлы конфигурации размещаются в:

```
~/.config/pipewire/
├── pipewire.conf          # Основная конфигурация демона
├── pipewire-pulse.conf    # Мост для PulseAudio
├── client.conf            # Настройки клиента по умолчанию
├── client-rt.conf         # Настройки клиента реального времени
└── jack.conf              # Слой совместимости с JACK
```

> ⚠️ **Внимание:** Существующие файлы конфигурации будут **перезаписаны**. Рекомендуется сделать резервную копию текущей конфигурации PipeWire, если у тебя есть кастомные изменения.

## 🔧 Устранение неполадок

| Проблема | Решение |
|----------|---------|
| `Cannot determine HOME directory` | Переменная окружения `$HOME` не задана. Выполни: `export HOME=/home/твоё_имя` |
| `DO NOT SUPPORT OS` | Отсутствует директория `~/.config`. Утилита предназначена для стандартного окружения Linux. |
| `PipeWire not installed` | Сначала установи PipeWire: `sudo apt install pipewire pipewire-pulse wireplumber` |
| `Failed restarting PipeWire services` | Перезапусти вручную: `systemctl --user restart pipewire.service pipewire-pulse.service wireplumber.service` |
| Звук всё ещё с высокой задержкой | Убедись, что другие звуковые серверы (PulseAudio, JACK) не запущены и не конфликтуют. |

---

<div align="center">

**[⬆ Back to Top](#-pipewire-setup-utility)**

*Made for the Linux Audio Community*

</div>
