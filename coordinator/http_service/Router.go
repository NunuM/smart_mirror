package http_service

import (
	"github.com/gorilla/mux"
	"net/http"
)


func New_router() *mux.Router{
	router:=mux.NewRouter()
	for _, route := range routes{
		var handler http.Handler
		handler = route.HandlerFunc
		router.Methods(route.Method).Path(route.Pattern).Name(route.Name).Handler(handler)
	}
	return router
}