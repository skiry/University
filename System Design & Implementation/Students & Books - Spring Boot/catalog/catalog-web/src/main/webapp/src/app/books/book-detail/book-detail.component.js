"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var core_1 = require('@angular/core');
require('rxjs/add/operator/switchMap');
var BookDetailComponent = (function () {
    function BookDetailComponent(bookService, route, location) {
        this.bookService = bookService;
        this.route = route;
        this.location = location;
    }
    BookDetailComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params
            .switchMap(function (params) { return _this.bookService.getBook(+params['id']); })
            .subscribe(function (book) { return _this.book = book; });
    };
    BookDetailComponent.prototype.goBack = function () {
        this.location.back();
    };
    __decorate([
        core_1.Input()
    ], BookDetailComponent.prototype, "book", void 0);
    BookDetailComponent = __decorate([
        core_1.Component({
            selector: 'ubb-book-detail',
            templateUrl: './book-detail.component.html',
            styleUrls: ['./book-detail.component.css'],
        })
    ], BookDetailComponent);
    return BookDetailComponent;
}());
exports.BookDetailComponent = BookDetailComponent;
