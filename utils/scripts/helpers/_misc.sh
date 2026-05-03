#!/usr/bin/env bash

# might only support Bash and Zsh

detect_shell_name() {
    local shell_path=${SHELL:-}

    if [[ -n "$shell_path" ]]; then
        basename "$shell_path"
        return 0
    fi

    basename "${0:-sh}"
}

detect_shell_rc_file() {
    local shell_name

    shell_name=$(detect_shell_name)

    case "$shell_name" in
        bash)
            printf '%s\n' "$HOME/.bashrc"
            ;;
        zsh)
            printf '%s\n' "$HOME/.zshrc"
            ;;
        fish)
            printf '%s\n' "$HOME/.config/fish/config.fish"
            ;;
        *)
            printf 'Unsupported or unknown shell: %s\n' "$shell_name" >&2
            return 1
            ;;
    esac
}

ensure_scriptlib_shell_block() {
    local rc_file=${1:-}

    if [[ -z "$rc_file" ]]; then
        printf 'Error: rc file required.\n' >&2
        return 1
    fi

    mkdir -p "$(dirname "$rc_file")"
    touch "$rc_file"

    if grep -q '# >>> scriptlib >>>' "$rc_file"; then
        printf 'scriptlib shell block already exists in %s\n' "$rc_file"
        return 0
    fi

    cat >> "$rc_file" <<'EOF'

# >>> scriptlib >>>
if [ -f "$HOME/.config/scriptlib/aliases.sh" ]; then
    . "$HOME/.config/scriptlib/aliases.sh"
fi
# <<< scriptlib <<<
EOF
}
# Later, uninstall.sh can remove that block.

