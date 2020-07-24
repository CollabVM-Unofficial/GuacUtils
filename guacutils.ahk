; Credit: Kekero/LoveEevee
chatcode := ["&", "&amp;", "'", "&#x27;", '"', "&quot;", "/", "&#x2F;", "<", "&lt;", ">", "&gt;"]

encodetext(cypher) {
	command := ""
	loop cypher.length(){
		current := cypher[a_index]
		command .= strlen(current) "." current
		command .= a_index == cypher.length() ? ";" : ","
	}
	return command
}
decodetext(string) {
	pos := 0
	sections := []
	while(true){
		len := instr(string, ".",, pos+1)
		if(len == 0){
			break
		}
		try{
			pos := substr(string, pos+1, len-pos-1) + len+1
		}catch{
			break
		}
		sections.push(substr(string, len+1, pos-len-1))
		if(substr(string, pos, pos+1) == ";"){
			break
		}
	}
	return sections
}
encodechat(text) {
	global chatcode
	i := 1
	while(i <= chatcode.length()){
		text := strreplace(text, chatcode[i], chatcode[i+1])
		i += 2
	}
	return text
}
decodechat(text) {
	global chatcode
	i := chatcode.length()
	while(i > 0){
		text := strreplace(text, chatcode[i], chatcode[i-1])
		i -= 2
	}
	return text
}
