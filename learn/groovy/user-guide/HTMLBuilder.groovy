import groovy.transform.CompileStatic
import groovy.transform.InheritConstructors
@CompileStatic
abstract class Tag {
   protected final StringBuilder sb
   Tag(StringBuilder sb) { this.sb = sb }
   
   void openTag() {}
   void closeTag() {}
   
   public void delegateToTag(Class clazz, Closure body) {
       Tag tag = (Tag) clazz.newInstance(sb)
       def clone = body.rehydrate(tag, this, this)
       tag.openTag()
       clone()
       tag.closeTag()
   }
}
@CompileStatic
class HTMLBuilder extends Tag {
   
   HTMLBuilder() { super(new StringBuilder()) }
   
   void html(@DelegatesTo(HTMLTag) Closure html) {
      delegateToTag(HTMLTag, html)
   }
   
   String getText() { sb }
   
   @InheritConstructors
   private static class HTMLTag extends Tag {
       void openTag() { sb.append '<html>' }
       void closeTag() { sb.append '</html>' }
       void body(@DelegatesTo(BodyTag) Closure body) {
           delegateToTag(BodyTag, body)
       }
       void head(@DelegatesTo(HeadTag) Closure head) { delegateToTag(HeadTag, head) }
   }
   @InheritConstructors
   private static class BodyTag extends Tag {
       void openTag() { sb.append '<body>' }
       void closeTag() { sb.append '</body>' }
       void p(String body) { sb << body }       
       void p(@DelegatesTo(PTag) Closure p) {
          delegateToTag(PTag, p)
       }
   }
   @InheritConstructors
   private static class HeadTag extends Tag {
       void openTag() { sb.append '<head>' }
       void closeTag() { sb.append '</head>' }      
   }
   @InheritConstructors
   static class PTag extends Tag {
      void openTag() { sb << "<p>" }
      void closeTag() { sb << "</p>" }
   }
}
@CompileStatic
String test() {
    def builder = new HTMLBuilder()
    builder.html {
       body {
          p 'Hello, static builder!'
          p {
              sb << 'Inside!'
          }
       }
    }
    builder.text
}
test()