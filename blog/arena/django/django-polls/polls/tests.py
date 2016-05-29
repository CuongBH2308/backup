import datetime
from django.utils import timezone
from django.test import TestCase
from django.core.urlresolvers import reverse

from polls.models import Poll

#python manage.py test -v 2 polls
class PollMethodTests(TestCase):
    def test_was_published_recently_with_future_poll(self):
        # a future post should not be a recent post
        future_poll = Poll(pub_date=timezone.now() + datetime.timedelta(days=30))
        self.assertEqual(future_poll.was_published_recently(), False)

    def test_was_published_recently_with_in_one_today(self):
        future_poll = Poll(pub_date=timezone.now() - datetime.timedelta(hours=10))
        self.assertEqual(future_poll.was_published_recently(), True)
        
    def test_was_published_recently_2_days_ago(self):
        future_poll = Poll(pub_date=timezone.now() - datetime.timedelta(days=2))
        self.assertEqual(future_poll.was_published_recently(), False)
        
        
def create_poll(question, days):
    return Poll.objects.create(question=question, pub_date=timezone.now() + datetime.timedelta(days=days))

class PollViewTest(TestCase):
    def test_index_view_with_no_polls(self):
        # use self.client.get to retrieve a response for a request
        response = self.client.get(reverse('polls:index'))
        self.assertEqual(response.status_code, 200)
        self.assertContains(response, "No polls are available.")
        self.assertQuerysetEqual(response.context['latest_poll_list'], [])
        
    def test_index_view_with_past_poll(self):
        create_poll(question="Past poll.", days=-30)
        response = self.client.get(reverse('polls:index'))
        self.assertQuerysetEqual(
            response.context['latest_poll_list'],
            ['<Poll: Past poll.>']
        )
        
class PollIndexDetailTests(TestCase):
    def test_detail_view_with_a_future_poll(self):
        future_poll = create_poll(question='Future poll.', days=5)
        response = self.client.get(reverse('polls:detail', args=(future_poll.id,)))
        self.assertEqual(response.status_code, 404)
    
    def test_detail_view_with_a_past_poll(self):
        past_poll = create_poll(question='Past poll.', days=-5)
        response = self.client.get(reverse('polls:detail', args=(past_poll.id,)))
        self.assertContains(response, past_poll.question, status_code=200)