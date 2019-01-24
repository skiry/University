"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var core_1 = require('@angular/core');
var BookListComponent = (function () {
    function BookListComponent(bookService, router) {
        this.bookService = bookService;
        this.router = router;
    }
    BookListComponent.prototype.ngOnInit = function () {
        this.getBooks();
    };
    BookListComponent.prototype.getBooks = function () {
        var _this = this;
        this.bookService.getBooks()
            .subscribe(function (books) { return _this.books = books; }, function (error) { return _this.errorMessage = error; });
    };
    BookListComponent.prototype.onSelect = function (book) {
        this.selectedBook = book;
    };
    BookListComponent.prototype.gotoDetail = function () {
        this.router.navigate(['/book/detail', this.selectedBook.id]);
    };
    BookListComponent = __decorate([
        core_1.Component({
            moduleId: module.id,
            selector: 'ubb-book-list',
            templateUrl: './book-list.component.html',
            styleUrls: ['./book-list.component.css'],
        })
    ], BookListComponent);
    return BookListComponent;
}());
exports.BookListComponent = BookListComponent;
