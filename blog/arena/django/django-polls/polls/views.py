from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, HttpResponseRedirect
from django.http import Http404
from django.views.generic import ListView
from django.views import generic
from django.core.urlresolvers import reverse
from polls.models import Poll, Choice
from django.utils import timezone

class IndexView(ListView):
    template_name = 'polls/index.html'
    context_object_name = 'latest_poll_list'
    def get_queryset(self):
        return Poll.objects.filter(
            pub_date__lte = timezone.now()
        ).order_by('-pub_date')[:5]
    

class DetailView(generic.DetailView):
    model = Poll
    template_name = 'polls/details.html'
    def get_queryset(self):
        return Poll.objects.filter(pub_date__lte=timezone.now())
    
def detail(request, poll_id):
    """
    try:
        poll = Poll.objects.get(pk=poll_id)
    except Poll.DoesNotExist:
        raise Http404
    """
    poll = get_object_or_404(Poll, pk=poll_id)
    return render(request, 'polls/details.html', {'poll': poll})

class ResultsView(generic.DetailView):
    model = Poll
    template_name = 'polls/results.html'
    def get_queryset(self):
        return Poll.objects.filter(pub_date__lte=timezone.now())
    
def results(request, poll_id):
    poll = get_object_or_404(Poll, pk=poll_id)
    return render(request, 'polls/results.html', {'poll': poll})

def vote(request, poll_id):
    p = get_object_or_404(Poll, pk=poll_id)
    try:
        selected_choice = p.choice_set.get(pk=request.POST['choice'])
    except (KeyError, Choice.DoesNotExist):
        # Redisplay the poll voting form
        return render(request, 'polls/details.html', {
            'poll': p,
            'error_message': "You didn't select a choice.",
        })
    else:
        selected_choice.votes += 1
        selected_choice.save()
        
        # always return an HttpResponseRedirect after successfully
        # with POST data, This prevents data from bing posted twice
        # if the user hits the Back button
        return HttpResponseRedirect(reverse('polls:results', args=(p.id,)))




from django import forms

class ContactForm(forms.Form):
    subject = forms.CharField(max_length=100)
    message = forms.CharField()
    sender = forms.EmailField()
    cc_myself = forms.BooleanField(required=False)



def contact(request):
    if request.method == 'POST':
        form = ContactForm(request.POST)
        # how to log in django?
        if form.is_valid():
            subject = form.cleaned_data['subject']
            message = form.cleaned_data['message']
            sender = form.cleaned_data['sender']
            cc_myself = form.cleaned_data['cc_myself']

            recipients = ['baiyanhuang@126.com']
            if cc_myself:
                recipients.append(sender)

            from django.core.mail import send_mail
            send_mail(subject, message, sender, recipients)

            #return HttpResponseRedirect('/thanks/')
            return HttpResponse('Thanks')
    else:
        form = ContactForm()

    return render(request, 'polls/contact.html', {'form': form})

