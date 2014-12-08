/**
 * stickyElement
 *
 * Makes the element sticky
 */
function stickyElement(elementClass, anchorClass) {
    var move = function() {
        var st = $(window).scrollTop();
        var ot = $("." + anchorClass).offset().top;
        var s = $("." + elementClass);
        if(st > ot) {
            s.css({
                position: "fixed",
                top: "0px"
            });
        } else {
            if(st <= ot) {
                s.css({
                    position: "relative",
                    top: ""
                });
            }
        }
    };
    $(window).scroll(move);
    move();
}
