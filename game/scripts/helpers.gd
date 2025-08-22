
#func _indent_lines(text: String, prefix: String) -> String:
	#var out := PackedStringArray()
	#for line in text.split("\n", false):
		#out.push_back(prefix + line)
	#return "\n".join(out)
#
#func format_bestiary_console(entry: BestiaryEntryResource) -> String:
	#var t := PackedStringArray()
#
	## Header
	#var header := "\n--- %s" % entry.get_name()
	#var lt := entry.get_lore_title()
	#if lt != "":
		#header += " - %s" % lt
	#header += " ---\n"
	#t.push_back(header)
#
	## Quote
	#var quote := entry.get_lore_quote()
	#if quote != "":
		#t.push_back("\"%s\"\n" % quote)
#
	## Flavor description bullets
	#for line in entry.get_lore_flavor_description():
		#t.push_back("%s\n" % line)
#
	#t.push_back("\n---\n\n")
	#t.push_back("Bestiary Entry\n")
	#t.push_back("Type:           %s\n" % entry.get_type())
	#t.push_back("Threat Level:   %s\n" % entry.get_threat_level())
	#t.push_back("First Emerged:  %s\n\n" % entry.get_first_emerged())
#
	## Long sections with indentation/bullets
	#if entry.get_description() != "":
		#t.push_back("Description:\n")
		#t.push_back(_indent_lines(entry.get_description(), "  ") + "\n\n")
#
	#if entry.get_hue_interaction() != "":
		#t.push_back("Hue Interaction:\n")
		#t.push_back(_indent_lines(entry.get_hue_interaction(), "  • ") + "\n\n")
#
	#if entry.get_behavior() != "":
		#t.push_back("Behavior:\n")
		#t.push_back(_indent_lines(entry.get_behavior(), "  • ") + "\n\n")
#
	#if entry.get_weaknesses() != "":
		#t.push_back("Known Weaknesses:\n")
		#t.push_back(_indent_lines(entry.get_weaknesses(), "  • ") + "\n\n")
#
	#if entry.get_notes() != "":
		#t.push_back("Notes:\n")
		#t.push_back(_indent_lines(entry.get_notes(), "  ") + "\n")
#
	## Lore entry (field notes)
	#var notes := entry.get_lore_field_notes()
	#if notes.size() > 0:
		#t.push_back("\n---\n\n")
		#var src := entry.get_lore_source()
		#t.push_back("Lore Entry%s\n\n" % (" - " + src if src != "" else ""))
		#for n in notes:
			#t.push_back("\"%s\"\n\n" % n)
#
	## Drops
	#var drops := entry.get_drops()
	#if drops.size() > 0:
		#t.push_back("\nDrops:\n")
		#for d in drops:
			#t.push_back("  • %s\n" % d)
#
	#return "".join(t)
#

#####
