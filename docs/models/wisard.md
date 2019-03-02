# Wisard
## Constructors
### Type 1
```python
wsd = Wisard(
       addressSize,               # type: int
       bleachingActivated=True,   # type: bool
       ignoreZero=False,          # type: bool
       completeAddressing=True,   # type: bool
       verbose=False,             # type: bool
       indexes=[],                # type: List[float]
       base=2,                    # type: int
       confidence=1,              # type: int

   ## types of return of classify
   returnActivationDegree=False,  # type: bool
   returnConfidence=False,        # type: bool
   returnClassesDegrees=False     # type: bool
)
```
##### addressSize: int 
Required. Size of RAM addresses.
##### bleachingActivated: bool 
Optional. Enables or disables the classification bleaching process. `True` by default.
##### ignoreZero: bool 
Optional. Causes the wisard to read/ignore address zero in each RAM. `False` by default.
##### completeAddressing: bool 
Optional. Enables or disables the automatic completion of addresses in cases where the entry size is not divisible by the address size. This creates redundant information, but addresses every entry index. `True` by default.
##### verbose: bool 
Optional. Enable or disables priting of train() and classify() progress. May incur in severe performance reduction. `False` by default.
##### indexes: list[int] 
Optional. Populate this to use a specific entry addressing for the discriminators. All discriminators wiil use this addressing. Empty `List` by default.
##### base: int 
Optional. This is the base/radix of addresses, `2` by default as the default behavior is binary addressing.
##### confidence: int 
Optional. This is the difference between the number of active RAMs of the first and second discriminators classified. It is used in the classification process. `1` by default.

#### Types of return of classify:
These parameters default to `False` for performance reasons.
##### returnActivationDegree: bool
Optional. When `True`, appends the activation degree value to each output. `False` by default.
##### returnConfidence: bool
Optional. When `True`, appends the confidence value to each output. `False` by default.
##### returnClassesDegrees: bool
Optional. When `True`, outputs the list of degrees of each class. `False` by default.

The appended return of `classify()` when any of the three enabled is a list of dictionaries in the following format:
```python
[
  {'class': 'cold', 'activationDegree': 1.0, 'confidence': 0.800000011920929},
  {'class': 'hot', 'activationDegree': 1.0, 'confidence': 1.0}
]
```
If only one of them is `True`, only one item will appear in the dictionary, and so on and so forth.
When all are `False`, `classify()` will return a list of strings.

### Type 2
```python
jsonConfig = wsd.json()
wsd2 = Wisard(jsonConfig)
```
The wisard can be saved with json or jsonConfig methods and reloaded later with this value.

## Methods
### train
This method train with the data passed to it.
```python

# load input data, just zeros and ones  
X = [
      [1,1,1,0,0,0,0,0],
      [1,1,1,1,0,0,0,0],
      [0,0,0,0,1,1,1,1],
      [0,0,0,0,0,1,1,1]
    ]

# load label data, which must be a string array
y = [
      "cold",
      "cold",
      "hot",
      "hot"
    ]

wsd.train(X, y)
```
### classify
This method classify the data passed to it, based on what it learn.
```python

# load input data, just zeros and ones  
X = [
      [1,1,1,0,0,0,0,0],
      [1,1,1,1,0,0,0,0],
      [0,0,0,0,1,1,1,1],
      [0,0,0,0,0,1,1,1]
    ]

# the output is a list of string, this represent the classes attributed to each input
out = wsd.classify(X)

for oneout in out:
    print(oneout)
```
- **X: [list(list(int))]** This is the list of inputs to be classified.

### getMentalImages
This one show the pattern learned by the model, it return a dictionary where the key is of type string and it is the class and value is the list of integer representing the learned pattern.
```python
patterns = wsd.getMentalImages()

for key in patterns:
    print(key, patterns[key])

```

### leaveOneOut
This will untrain an input trained before.
```python
x = [1,1,1,0,0,0,0,0]
wsd.leaveOneOut(x,"cold")
```

### leaveMoreOut
This will untrain a list of inputs trained before.
```python
X = [
   [1,1,1,0,0,0,0,0],
   [0,0,0,0,1,1,1,1],
]
y = [
   "cold",
   "hot"
]
wsd.leaveMoreOut(X,y)
```

### json
This return the configuration and ram values as JSON format converted to string.
```python
print("Wisard: ", wsd.json())
# or pass true as parameter to save ram data in files (this is useful for huge rams)
print("Wisard: ", wsd.json(True,"path/to/save/data"))
```

### jsonConfig
This do the same as json() method, but without ram values.
```python
print("Wisard: ", wsd.jsonConfig())
```
