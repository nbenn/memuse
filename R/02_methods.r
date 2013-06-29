### Method declarations
#setGeneric(name="print", 
#  useAsDefault=base::print, 
#  package="memuse"
#)

### Accessors
setGeneric(name="size", 
  function(x)
    standardGeneric("size"), 
  package="memuse"
)

setGeneric(name="unit", 
  function(x)
    standardGeneric("unit"), 
  package="memuse"
)

setGeneric(name="unit.prefix", 
  function(x)
    standardGeneric("unit.prefix"), 
  package="memuse"
)

setGeneric(name="unit.names", 
  function(x)
    standardGeneric("unit.names"), 
  package="memuse"
)


### Replacers
setGeneric(name="size<-", 
  function(x, value)
    standardGeneric("size<-"), 
  package="memuse"
)

setGeneric(name="unit<-", 
  function(x, value)
    standardGeneric("unit<-"), 
  package="memuse"
)

setGeneric(name="unit.prefix<-", 
  function(x, value)
    standardGeneric("unit.prefix<-"), 
  package="memuse"
)

setGeneric(name="unit.names<-", 
  function(x, value)
    standardGeneric("unit.names<-"), 
  package="memuse"
)


### Swaps
setGeneric(name="swap.unit", 
  function(x, unit)
    standardGeneric("swap.unit"), 
  package="memuse"
)

setGeneric(name="swap.prefix", 
  function(x) 
    standardGeneric("swap.prefix"),
  package="memuse"
)

setGeneric(name="swap.names", 
  function(x)
    standardGeneric("swap.names"), 
  package="memuse"
)


### Other
setGeneric(name="howmany", 
  function(x, ...)
    standardGeneric("howmany"), 
  package="memuse"
)

#setGeneric(name="as.numeric", 
#  useAsDefault=base::as.numeric, 
#  package="memuse"
#)
