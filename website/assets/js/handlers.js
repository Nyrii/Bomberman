jQuery(function() {
  function smoothScrollHandler() {
    $('.js-scrollTo').on('click', function() { // Au clic sur un élément
      var page = $(this).attr('href'); // Page cible
      var speed = 700; // Durée de l'animation (en ms)
      $('html, body').animate({
        scrollTop: $(page).offset().top
      }, speed); // Go
      return false;
    });

    $('.js-scrollTop').on('click', function() { // Au clic sur un élément
      var page = "#"; // Page cible
      var speed = 700; // Durée de l'animation (en ms)
      $('html, body').animate({
        scrollTop: 0
      }, speed ); // Go
      return false;
    });
  }

  function videoPlayerHandler() {
    $("#playerIntro video").css("height", $(window).height() / 2 + "px");
    $(window).resize(function() {
      $("#playerIntro video").css("height", $(window).height() / 2 + "px");
    });
    $("#playerButton").click(function(){
      var video = $("#playerIntro video");

      $("#playerIntro").toggleClass("playerOpened");
      setTimeout(function() {
        !video.paused ? video.get(0).play() : video.get(0).pause();
      }, 300);
    });

    $("#closeCross").click(function(){
      var video = $("#playerIntro video");

      $("#playerIntro").toggleClass("playerOpened");
      video.paused ? video.get(0).play() : video.get(0).pause();
    });
  }

  function initParallax() {
    if($('html').hasClass('no-js')) {
        var badIe = true;
    }

    if( badIe ) {
        $('.parallax').imageScroll({
            touch: true
        });
    }
    else {
        $('#headerwrap').parallax('50%', 0.6);

        $("body").localScroll(800);
    }
  }

  function isMobile() {
    if (navigator.userAgent.match(/Android/i) ||
      navigator.userAgent.match(/webOS/i) ||
      navigator.userAgent.match(/iPhone/i) ||
      navigator.userAgent.match(/iPad/i)||
      navigator.userAgent.match(/iPod/i) ||
      navigator.userAgent.match(/BlackBerry/i)) {
      return true;
    }
  }

  $(document).ready(function() {
      smoothScrollHandler();
      videoPlayerHandler();
      initParallax();
  });
});
