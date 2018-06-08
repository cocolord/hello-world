$(function() {	

	$("#about .accordion h1:gt(0)").removeClass('open');
	$("#about .accordion .accordion-content:gt(0)").css({
			display: "none"
		});

	$(".toolbar .twitter").mouseenter(function() {
		$(".weixin-img").css({
			display: "block"
		});
	});

	$(".toolbar .twitter").mouseleave(function() {
		$(".weixin-img").css({
			display: "none"
		});
	});

	$('.dropdown-top , .other-web').hover(function() {
		$(this).children().addClass('show');
	}, function() {
		$(this).children().removeClass('show');
	});	

	$(".products-buy , .tabbednav a , .video-box a, #home .videos .row a, #video .video-list a,.industry-carousel .industry-video a,.consumer-video a").click(function(event){
	  event.preventDefault();
	});		
	
	$(".video-post-list a").click(function(event){
	  event.preventDefault();
	  $(this).addClass('active').parent().siblings().children().removeClass("active");
	});	
	
	$('.products-buy').hover(function() {
		$(this).children().addClass('show');
	}, function() {
		$(this).children().removeClass('show');
	});	
	
	$(".video-post-list a").click(function(event){
	  event.preventDefault();
	  $(this).addClass('active').parent().siblings().children().removeClass("active");
	});	
	
	$('.video-post-list a').each(function() {
		this.onclick = function() {
			var linkhref = $(this).attr('video-date');
			$("#video-iframe iframe").attr("src", linkhref );
		};
	});
	
	$('.nav-chanping').hover(function() {
		$('.chanping-dropdown').addClass('show');
	}, function() {
		$('.chanping-dropdown').removeClass('show');
	});
	
	$('#responsive-navbar ul li').hover(function() {
		$(this).find('.dropdown').addClass('show');
	}, function() {
		$(this).find('.dropdown').removeClass('show');
	});	

	$('.tujian-list a').hover(function(e) {
		e.preventDefault()
		$(this).tab('show')
	});

	$('.item-list0 a').hover(function(e) {
		e.preventDefault()
		$(this).tab('show')
	});

	//手风琴
		var headers = ["H1"];
		$(".accordion").click(function(e) {
		  var target = e.target,
			  name = target.nodeName.toUpperCase();
		  
		  if($.inArray(name,headers) > -1) {
			var subItem = $(target).next();
			var depth = $(subItem).parents().length;
			var allAtDepth = $(".accordion div").filter(function() {
			  if($(this).parents().length >= depth && this !== subItem.get(0)) {
				return true; 
			  }
			});
			$(allAtDepth).slideUp("fast");
				subItem.slideToggle("fast",function() {
				$(".accordion :visible:last").css("border-radius","0");
			});
				$(target).toggleClass("open").siblings().removeClass("open");
		  }
		});
		

	
	//判断访问终端
	var browser = {
		versions: function() {
			var u = navigator.userAgent,
				app = navigator.appVersion;
			return {
				trident: u.indexOf('Trident') > -1,
				//IE内核
				presto: u.indexOf('Presto') > -1,
				//opera内核
				webKit: u.indexOf('AppleWebKit') > -1,
				//苹果、谷歌内核
				gecko: u.indexOf('Gecko') > -1 && u.indexOf('KHTML') == -1,
				//火狐内核
				mobile: !! u.match(/AppleWebKit.*Mobile.*/),
				//是否为移动终端
				ios: !! u.match(/\(i[^;]+;( U;)? CPU.+Mac OS X/),
				//ios终端
				android: u.indexOf('Android') > -1 || u.indexOf('Linux') > -1,
				//android终端或者uc浏览器
				iPhone: u.indexOf('iPhone') > -1,
				//是否为iPhone或者QQHD浏览器
				iPad: u.indexOf('iPad') > -1,
				//是否iPad
				webApp: u.indexOf('Safari') == -1,
				//是否web应该程序，没有头部与底部
				weixin: u.indexOf('MicroMessenger') > -1,
				//是否微信 （2015-01-22新增）
				qq: u.match(/\sQQ/i) == " qq" //是否QQ
			};
		}(),
		language: (navigator.browserLanguage || navigator.language).toLowerCase()
	}
	//判断是否移动端
	if (!(browser.versions.mobile || browser.versions.android || browser.versions.ios)) {
		$("#home #carousel-example-generic").css({
			"min-height": "400px"
		});
	}
});