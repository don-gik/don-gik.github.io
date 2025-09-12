---
layout: single
title: "Windows Powershell Setup, 그리고 쓰는 법"
excerpt: "PowerShell을 제대로 깔고 사용하는 법"
classes: wide
categories: [coding]
tags: [coding]
toc: false
---

<style>
    .page__content figure > figcaption {
        text-align: center !important;
        margin: -0.4rem 0 0 !important;
        padding: 0 !important;
        font-size: .95em;
        line-height: 1.35;
        background: transparent;
        border: 0;
    }
    img.center {
        display: block;
        margin-left: auto;
        margin-right: auto;
    }
</style>



PowerShell과 CMD는 Windows에서 굉장히 중요한 도구이다.

CMD는 Windows에서만 지원되는 Shell이지만, PowerShell은 MacOS, Windows, Linux 모두에서 지원된다.
그만큼 활용률이 높은 것이다. 그러니 한번 알아보도록 하자.


## PowerShell 설치

<div class="code-wrap-char">
{% highlight powershell linenos %}
winget install --id Microsoft.PowerShell --source winget
{% endhighlight %}
</div>

관리자 권한이 필요하다고 하면 관리자 권한 허용을 해주자.
이 명령어는 
<a href="https://learn.microsoft.com/ko-kr/powershell/scripting/install/installing-powershell-on-windows?view=powershell-7.5" target="_blank">여기</a>에서 참조한 것이다.

이제 PowerShell이 제대로 깔렸다면,

<div class="code-wrap-char">
{% highlight powershell linenos %}
exit
{% endhighlight %}
</div>

으로 나가주도록 하자.


## PowerShell 시작하기

모든 내용은 <a href="https://learn.microsoft.com/ko-kr/powershell/scripting/learn/ps101/01-getting-started?view=powershell-7.5" target="_blank">여기</a>
를 참조하고 있다.


PowerShell의 유일한 단점은 보안이 너무 튼튼하다는 것이다.
CMD처럼 관리자 권한을 sudo로 간편하게 얻을 수 없다.


따라서 다음 명령어도 관리자 권한이 없다면 실행이 불가하게 된다.
<div class="code-wrap-char">
{% highlight powershell linenos %}
Stop-Service -Name W32Time    # W32Time이라는 서비스를 정지
{% endhighlight %}
</div>

만약 **관리자 권한이 있다면** PowerShell은 거의 모든 작업을 할 수 있게 되지만,
보안상 관리자 권한을 남용하는 것은 추천되지 않는다.


PowerShell에서는 변수를 확인할 수도 있다.
<div class="code-wrap-char">
{% highlight powershell linenos %}
$PSVersionTable
{% endhighlight %}

{% highlight output linenos %}
Name                           Value
----                           -----
PSVersion                      5.1.22621.2428
PSEdition                      Desktop
PSCompatibleVersions           {1.0, 2.0, 3.0, 4.0...}
BuildVersion                   10.0.22621.2428
CLRVersion                     4.0.30319.42000
WSManStackVersion              3.0
PSRemotingProtocolVersion      2.3
SerializationVersion           1.1.0.1
{% endhighlight %}
</div>


이 경우, 컴퓨터의 버전 등을 확인할 수 있는 변수를 읽을 수 있다.
이를 **환경 변수**라고 한다.

## 쓸만한 PowerShell 명령어들

PowerShell을 제대로 깔면, Bash와 실제로 비슷한 명령어들이 많게 된다!
이를 지원하는 기능을 Alias라고 한다.

<div class="code-wrap-char">
{% highlight powershell linenos %}
ls                # Get-Childitem
mv                # Move-Item
cat               # Get-Content
cp                # Copy-Item
{% endhighlight %}
</div>

PowerShell의 기본 명령어들은 모두 Verb-Noun의 꼴로 되어있고,
이해하기 쉬운 언어로 되어있으니 나중에 심심하면 쉽게 공부할 수 있다.

만약 명령어에 대한 도움이 필요하다면,
<div class="code-wrap-char">
{% highlight powershell linenos %}
Get-Help {cmdlet-name}
{% endhighlight %}
</div>
을 사용하면 명령어의 사용법 등을 알려준다!
ls같은 경우 다르게 작동하니까, Get-Help ls를 하게 된다면...

<div class="code-wrap-char">
{% highlight output linenos %}
이름
    Get-ChildItem

구문
    Get-ChildItem [[-Path] <string[]>] [[-Filter] <string>]  [<CommonParameters>]

    Get-ChildItem [[-Filter] <string>]  [<CommonParameters>]


별칭
    gci
    ls
    dir


설명
    Get-Help가 이 컴퓨터에서 이 cmdlet에 대한 도움말 파일을 찾을 수 없습니다. 일부 도움말만 표시합니다.
        -- 이 cmdlet을 포함하는 모듈에 대한 도움말 파일을 다운로드하여 설치하려면 Update-Help를 사용하십시오.
        -- 이 cmdlet에 대한 도움말 항목을 온라인으로 보려면 "Get-Help Get-ChildItem -Online"을 입력하거나
           https://go.microsoft.com/fwlink/?LinkID=113308(으)로 이동하십시오.
{% endhighlight %}
</div>

이 기능은 조금 공부하기에는 좋지만, ~~개인적으로 딱히 큰 도움은 못주는 것 같다~~


## PowerShell에 대해서 조금씩 공부하는 법

Get-Childitem은 Linux에서처럼 ls -al같은 것들이 지원이 되지 않는다.

그럼 어떻게 이용하는 걸까?

<a href="https://learn.microsoft.com/ko-kr/powershell/module/microsoft.powershell.management/?view=powershell-7.5">여기</a>에서 모든 해답을 찾을 수 있다.
Get-Childitem을 검색해서 설명을 보면,

<div class="code-wrap-char">
{% highlight powershell linenos %}
Get-Childitem -Path {path}              # ls {path}
Get-Childitem -Path {path} -Recurse     # ls -R {path}
Get-Childitem -Path {path} -Force       # ls -a {path}
{% endhighlight %}
</div>

이런 식으로 기본적인 사실들을 알아갈 수 있다.
사용법을 익힌다면 Bash가 더 편하겠지만, 처음에 Shell을 배워가는 사람으로써는
PowerShell이 훨씬 더 직관적인 커맨드를 가지고 있는 것 같다.

-------------------------

오늘은 PowerShell을 제대로 설치하고, 한 번 이용해보는 법에 대해서 알아보았다.
이걸 읽고 Shell와 x86, ARM architecture 같이 컴퓨터 자체에 관심이 생기는 사람이 생겼으면 좋겠다.