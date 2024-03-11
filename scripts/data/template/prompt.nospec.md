## system

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation. For the function $sin(x)$, assuming an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, a metamorphic relation $sin(x)=sin(\pi-x)$ exists. You are an expert on metamorphic testing.

## user

Please identify the metamorphic relation of the program `[sut_name]` as much as possible and codify them. Note that you should just output the code block. Here are some examples:

[demo]

## user

Please identify more different metamorphic relations of this program and codify them.