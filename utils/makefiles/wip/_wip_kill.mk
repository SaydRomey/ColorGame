
# Macro: KILL_PROCESS_BY_NAME
# Kills processes matching the given name.
#
# Parameters:
# $(1): Process name (string) to search for (partial match allowed).
# $(2): (Optional) "print" to list PIDs before killing.
#
# Example Usage:
#   $(call KILL_PROCESS_BY_NAME,godot)        # kill silently
#   $(call KILL_PROCESS_BY_NAME,godot,print)  # print PIDs first
#
define KILL_PROCESS_BY_NAME
	$(call CHECK_COMMAND,pgrep)
	PIDS=$$(pgrep -f $(1)); \
	if [ -n "$$PIDS" ]; then \
		$(call INFO,KILL,Process '$(1)' found:); \
		if [ "$(2)" = "print" ]; then \
			for PID in $$PIDS; do \
				printf "\t\t$(ORANGE)%s$(RESET)\n" "$$PID"; \
			done; \
		fi; \
		kill -9 $$PIDS; \
		$(call SUCCESS,KILL,Killed process(es) named '$(1)'.); \
	else \
		$(call WARNING,KILL,No process found matching '$(1)'.); \
	fi
endef

.PHONY: kill
kill:
	@bash -c '\
		read -p "Enter process name to kill: " pname; \
		if [ -z "$$pname" ]; then \
			echo "❌ No process name provided."; exit 1; \
		fi; \
		exec make __kill-by-name PROCESS_NAME="$$pname" --no-print-directory \
	'

__kill-by-name:
	@$(call KILL_PROCESS_BY_NAME,$(PROCESS_NAME),print)