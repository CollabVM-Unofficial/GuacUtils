// Credit: Some guest on CollabVM who posted this to pastebin.
import java.util.*;

class GuacUtil {
    static String EncodeGuac(final String... cypher) {
        final StringBuilder command = new StringBuilder();
        for (int i = 0; i < cypher.length; i++) {
            final String current = cypher[i];
            command.append(current.length());
            command.append('.');
            command.append(current);
            command.append(i < cypher.length - 1 ? ',' : ';');
        }

        return command.toString();
    }

    static String[] DecodeGuac(final String str) {
        int pos = -1;
        final ArrayList<String> sections = new ArrayList<>();

        for (;;) {
            final int len = str.indexOf('.', pos + 1);
            if (len == -1) {
                break;
            }

            pos = Integer.parseInt(str.substring(pos + 1, pos + 1 + len - (pos + 1))) + len + 1;
            String repl = str.substring(len + 1, len + 1 + pos - (len + 1));
            repl = repl.replaceAll("&#x27;", "'").replaceAll("&quot;", "\"").replaceAll("&#x2F;", "/")
                    .replaceAll("&lt;", "<").replaceAll("&gt;", ">").replaceAll("&amp;", "&");
            sections.add(repl);

            if (str.substring(pos, pos + 1).equals(";")) {
                break;
            }
        }

        return sections.toArray(new String[0]);
    }
}