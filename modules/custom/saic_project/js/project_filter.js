/**
 * Project filter block
 */
 
$(document).ready(function () {
$('.view-id-featured_projects .views-row')
    .hover(function () {
        $(this).addClass('featuredHoverOn');
    }, function () {
        $(this).removeClass('featuredHoverOn');    
    })
    .bind('click', function () {
        window.location = $(this).find('strong a').attr('href');
        return false;
    });
});

