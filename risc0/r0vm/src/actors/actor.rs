// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::fmt;
use std::future::Future;
use std::pin::Pin;
use std::sync::{Arc, Mutex, Weak};

use tokio::sync::{broadcast, mpsc, oneshot};

/// An object that will run on a task receiving messages
pub trait Actor: Sized + Send + 'static {
    fn on_start(&mut self, _actor_ref: ActorRef<Self>) -> impl Future<Output = ()> + Send {
        async {}
    }

    fn on_stop(&mut self) -> impl Future<Output = ()> + Send {
        async {}
    }
}

#[derive(Debug, PartialEq, Eq, Clone)]
pub enum SendError {
    /// The actor we are trying to communicate is no longer accepting messages.
    ActorNotRunning,
    /// The actor didn't reply to our message when the caller was expecting a reply.
    NoReply,
}

impl std::error::Error for SendError {}

impl fmt::Display for SendError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::ActorNotRunning => write!(f, "actor not running"),
            Self::NoReply => write!(f, "actor didn't reply"),
        }
    }
}

/// The number of messages that will queue up for an actor before tell/ask start waiting for room.
const MAILBOX_SIZE: usize = 64;

/// Spawn a new task which receives messages for the actor.
pub fn spawn<ActorT: Actor>(actor: ActorT) -> ActorRef<ActorT> {
    ActorTask::spawn(actor)
}

/// An object that can receive a reply from an actor to a previously sent message.
pub struct PendingReply<ReplyT: 'static> {
    reply: oneshot::Receiver<Result<ReplyT, SendError>>,
}

impl<ReplyT: 'static> PendingReply<ReplyT> {
    /// Receive a reply from a previously sent message. If the actor isn't running
    /// `SendError::ActorNotRunning` is returned. If the actor doesn't reply to the message,
    /// `lSendError::NoReply` is returned.
    pub async fn recv(self) -> Result<ReplyT, SendError> {
        self.reply.await.map_err(|_| SendError::ActorNotRunning)?
    }
}

type HandleMessageFn<ActorT> =
    Box<dyn for<'a> FnOnce(&'a mut ActorT) -> Pin<Box<dyn Future<Output = ()> + Send + 'a>> + Send>;

/// The send side of a channel that communicates with the actor task.
struct ActorSender<ActorT>(mpsc::Sender<HandleMessageFn<ActorT>>);

impl<ActorT: Actor> Clone for ActorSender<ActorT> {
    fn clone(&self) -> Self {
        Self(self.0.clone())
    }
}

impl<ActorT: Actor> ActorSender<ActorT> {
    async fn send(&self, msg_fn: HandleMessageFn<ActorT>) -> Result<(), SendError> {
        self.0
            .send(msg_fn)
            .await
            .map_err(|_| SendError::ActorNotRunning)
    }

    fn blocking_send(&self, msg_fn: HandleMessageFn<ActorT>) -> Result<(), SendError> {
        self.0
            .blocking_send(msg_fn)
            .map_err(|_| SendError::ActorNotRunning)
    }
}

/// Represents the tokio task which is receiving messages and delivering them to an actor.
struct ActorTask<ActorT: Actor> {
    sender: Option<ActorSender<ActorT>>,
    task_handle: tokio::task::JoinHandle<()>,
    stop: broadcast::Receiver<()>,
}

/// The main recv loop for an actor
async fn actor_task_main<ActorT: Actor>(
    mut actor: ActorT,
    actor_ref: ActorRef<ActorT>,
    mut recv: mpsc::Receiver<HandleMessageFn<ActorT>>,
) {
    actor.on_start(actor_ref).await;

    while let Some(handle_msg) = recv.recv().await {
        handle_msg(&mut actor).await
    }

    actor.on_stop().await;
}

impl<ActorT: Actor> ActorTask<ActorT> {
    fn spawn(actor: ActorT) -> ActorRef<ActorT> {
        let (send, recv) = mpsc::channel(MAILBOX_SIZE);

        let (stop_send, stop_recv) = broadcast::channel(1);
        let (actor_ref_send, actor_ref_recv) = oneshot::channel();
        let task_handle = tokio::task::spawn(async move {
            let actor_ref = actor_ref_recv
                .await
                .expect("actor_ref_send should still exist");
            actor_task_main(actor, actor_ref, recv).await;
            drop(stop_send);
        });

        let actor_task = Arc::new(Mutex::new(Self {
            sender: Some(ActorSender(send)),
            task_handle,
            stop: stop_recv,
        }));

        let actor_ref = ActorRef { task: actor_task };
        actor_ref_send
            .send(actor_ref.clone())
            .map_err(|_| ())
            .expect("task should still be running");
        actor_ref
    }

    fn sender(&self) -> Result<ActorSender<ActorT>, SendError> {
        self.sender.clone().ok_or(SendError::ActorNotRunning)
    }

    fn stop(&mut self) -> bool {
        self.sender.take().is_some()
    }

    fn kill(&mut self) {
        self.task_handle.abort();
    }

    fn stop_waiter(&self) -> broadcast::Receiver<()> {
        self.stop.resubscribe()
    }
}

pub struct ActorRef<ActorT: Actor> {
    task: Arc<Mutex<ActorTask<ActorT>>>,
}

impl<ActorT: Actor> Clone for ActorRef<ActorT> {
    fn clone(&self) -> Self {
        Self {
            task: self.task.clone(),
        }
    }
}

impl<ActorT: Actor> ActorRef<ActorT> {
    /// Send a message to an actor and wait for a response. If the actor doesn't reply,
    /// `SendError::NoReply` is returned. If the actor is no longer running,
    /// `SendError::ActorNotRunning` is returned.
    pub async fn ask<MessageT>(
        &self,
        msg: MessageT,
    ) -> Result<<ActorT as Message<MessageT>>::Reply, SendError>
    where
        MessageT: Send + 'static,
        ActorT: Message<MessageT>,
    {
        let pending_reply = self.ask_enqueue(msg).await?;
        pending_reply.recv().await
    }

    /// Send a message to an actor and return an object which can be used to wait for a reply.
    pub async fn ask_enqueue<MessageT>(
        &self,
        msg: MessageT,
    ) -> Result<PendingReply<<ActorT as Message<MessageT>>::Reply>, SendError>
    where
        MessageT: Send + 'static,
        ActorT: Message<MessageT>,
    {
        let actor_ref = self.clone();
        let (sender, reply) = oneshot::channel();
        let reply_sender = ReplySender { sender };

        let sender = self.task.lock().unwrap().sender()?;
        sender
            .send(Box::new(move |actor| {
                Box::pin(async move {
                    let mut context = Context {
                        actor_ref,
                        reply_sender: Some(reply_sender),
                    };
                    Message::handle(actor, msg, &mut context).await;
                })
            }))
            .await?;
        Ok(PendingReply { reply })
    }

    /// Send a message to an actor and don't wait for a reply.
    pub async fn tell<MessageT>(&self, msg: MessageT) -> Result<(), SendError>
    where
        MessageT: Send + 'static,
        ActorT: Message<MessageT>,
    {
        let actor_ref = self.clone();
        let sender = self.task.lock().unwrap().sender()?;
        sender
            .send(Box::new(move |actor| {
                Box::pin(async move {
                    let mut context = Context {
                        actor_ref,
                        reply_sender: None,
                    };
                    Message::handle(actor, msg, &mut context).await;
                })
            }))
            .await
    }

    /// Send a message to an actor and don't wait for a reply and do so by blocking.
    pub fn tell_blocking<MessageT>(&self, msg: MessageT) -> Result<(), SendError>
    where
        MessageT: Send + 'static,
        ActorT: Message<MessageT>,
    {
        let actor_ref = self.clone();
        let sender = self.task.lock().unwrap().sender()?;
        sender.blocking_send(Box::new(move |actor| {
            Box::pin(async move {
                let mut context = Context {
                    actor_ref,
                    reply_sender: None,
                };
                Message::handle(actor, msg, &mut context).await;
            })
        }))
    }

    async fn forward<MessageT>(
        &self,
        msg: MessageT,
        reply_sender: Option<ReplySender<<ActorT as Message<MessageT>>::Reply>>,
    ) -> Result<(), SendError>
    where
        MessageT: Send + 'static,
        ActorT: Message<MessageT>,
    {
        let actor_ref = self.clone();
        let sender = self.task.lock().unwrap().sender()?;
        sender
            .send(Box::new(move |actor| {
                Box::pin(async move {
                    let mut context = Context {
                        actor_ref,
                        reply_sender,
                    };
                    Message::handle(actor, msg, &mut context).await;
                })
            }))
            .await
    }

    /// Tell the actor to stop. After this call returns, any attempt to send a message to the actor
    /// will error with `SendError::ActorNotRunning`. The actor will process all existing messages
    /// in its queue before exiting.
    pub async fn stop_gracefully(&self) -> Result<(), SendError> {
        if self.task.lock().unwrap().stop() {
            Ok(())
        } else {
            Err(SendError::ActorNotRunning)
        }
    }

    /// Wait for an actor to be no longer processing messages and destroyed.
    pub async fn wait_for_stop(&self) {
        let mut waiter = self.task.lock().unwrap().stop_waiter();
        let _ = waiter.recv().await;
    }

    /// Abort the task running the actor. This will cause it to exit as soon as it reaches an await
    /// point.
    pub fn kill(&self) {
        self.task.lock().unwrap().kill();
    }

    /// Receive a weak reference to this actor.
    pub fn downgrade(&self) -> WeakActorRef<ActorT> {
        WeakActorRef {
            task: Arc::downgrade(&self.task),
        }
    }
}

/// A weak reference to an actor. Holding this reference will not stop an actor from being
/// destroyed once all `ActorRef` are destroyed.
pub struct WeakActorRef<ActorT: Actor> {
    task: Weak<Mutex<ActorTask<ActorT>>>,
}

impl<ActorT: Actor> WeakActorRef<ActorT> {
    /// Attempt to upgrade to an `ActorRef`. If the underlying actor has already been destroyed,
    /// this will return `None`.
    pub fn upgrade(&self) -> Option<ActorRef<ActorT>> {
        self.task.upgrade().map(|task| ActorRef { task })
    }
}

impl<ActorT: Actor> Clone for WeakActorRef<ActorT> {
    fn clone(&self) -> Self {
        Self {
            task: self.task.clone(),
        }
    }
}

pub struct ReplySender<ValueT: Send + 'static> {
    sender: oneshot::Sender<Result<ValueT, SendError>>,
}

impl<ValueT: Send + 'static> ReplySender<ValueT> {
    pub fn send(self, value: ValueT) {
        // If the other side is no longer listening, we throw away the reply
        let _ = self.sender.send(Ok(value));
    }

    pub fn no_reply(self) {
        let _ = self.sender.send(Err(SendError::NoReply));
    }
}

/// This type is passed to `Message::handle` and mainly allows the actor to reply to the given
/// message.
pub struct Context<ActorT: Actor, ReplyT: Send + 'static> {
    actor_ref: ActorRef<ActorT>,
    reply_sender: Option<ReplySender<ReplyT>>,
}

impl<ActorT: Actor, ReplyT: Send + 'static> Drop for Context<ActorT, ReplyT> {
    fn drop(&mut self) {
        if let Some(reply_sender) = self.reply_sender.take() {
            reply_sender.no_reply()
        }
    }
}

impl<ActorT: Actor, ReplyT: Send + 'static> fmt::Debug for Context<ActorT, ReplyT> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Context").finish_non_exhaustive()
    }
}

impl<ActorT: Actor, ReplyT: Send + 'static> Context<ActorT, ReplyT> {
    /// If the sender of the message is expecting a reply, this will return an object that can be
    /// used to send a reply. If this object is destroyed without sending a reply, the sender will
    /// receive `SendError::NoReply`.
    pub fn reply_sender(&mut self) -> Option<ReplySender<ReplyT>> {
        self.reply_sender.take()
    }

    /// If the sender of the message is expecting a reply, send the given message as a reply to
    /// them. Otherwise, if they aren't just ignore the given message.
    pub fn reply(&mut self, msg: ReplyT) {
        if let Some(reply_sender) = self.reply_sender.take() {
            reply_sender.send(msg);
        }
    }

    /// Forward this message to another actor. They will take on the burden of replying.
    pub async fn forward<OtherActorT, MessageT>(
        &mut self,
        other: &ActorRef<OtherActorT>,
        msg: MessageT,
    ) where
        OtherActorT: Message<MessageT, Reply = ReplyT>,
        MessageT: Send + 'static,
    {
        // ignore error if other actor isn't running, instead the pending reply will get an error
        let _ = other.forward(msg, self.reply_sender()).await;
    }

    /// Get a ref to the current actor.
    pub fn actor_ref(&self) -> ActorRef<ActorT> {
        self.actor_ref.clone()
    }
}

/// The ability to receive and possible reply to a certain message.
pub trait Message<MessageT>: Actor {
    type Reply: Send + 'static;

    fn handle(
        &mut self,
        msg: MessageT,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> impl Future<Output = ()> + Send;
}

#[cfg(test)]
mod tests {
    use std::sync::atomic::{AtomicBool, Ordering};

    use super::*;
    use tokio::sync::mpsc::{UnboundedReceiver, UnboundedSender, unbounded_channel};

    #[derive(Clone, Debug, PartialEq, Eq)]
    struct Ping(u32);

    #[derive(Clone, Debug, PartialEq, Eq)]
    struct Bang(u32);

    #[derive(Clone, Debug, PartialEq, Eq)]
    struct Pong(u32);

    struct TestActor {
        ping: UnboundedSender<Ping>,
        bang: UnboundedSender<Bang>,
        started: Arc<AtomicBool>,
        stopped: Arc<AtomicBool>,
    }

    struct TestActorSpy {
        ping: UnboundedReceiver<Ping>,
        bang: UnboundedReceiver<Bang>,
        started: Arc<AtomicBool>,
        stopped: Arc<AtomicBool>,
    }

    impl TestActor {
        fn new() -> (Self, TestActorSpy) {
            let (ping_send, ping_recv) = unbounded_channel();
            let (bang_send, bang_recv) = unbounded_channel();
            let started = Arc::new(AtomicBool::new(false));
            let stopped = Arc::new(AtomicBool::new(false));
            (
                Self {
                    ping: ping_send,
                    bang: bang_send,
                    started: started.clone(),
                    stopped: stopped.clone(),
                },
                TestActorSpy {
                    ping: ping_recv,
                    bang: bang_recv,
                    started,
                    stopped,
                },
            )
        }
    }

    impl Actor for TestActor {
        async fn on_start(&mut self, _actor_ref: ActorRef<Self>) {
            self.started.store(true, Ordering::Release);
        }

        async fn on_stop(&mut self) {
            self.stopped.store(true, Ordering::Release);
        }
    }

    impl Message<Ping> for TestActor {
        type Reply = Pong;

        async fn handle(&mut self, msg: Ping, ctx: &mut Context<Self, Self::Reply>) {
            self.ping
                .send(msg.clone())
                .expect("messages should only be received when expected");
            ctx.reply(Pong(msg.0));
        }
    }

    impl Message<Bang> for TestActor {
        type Reply = Pong;

        async fn handle(&mut self, msg: Bang, _ctx: &mut Context<Self, Self::Reply>) {
            self.bang
                .send(msg.clone())
                .expect("messages should only be received when expected");
        }
    }

    struct ForwardingActor(ActorRef<TestActor>);

    impl Actor for ForwardingActor {}

    impl Message<Ping> for ForwardingActor {
        type Reply = Pong;

        async fn handle(&mut self, msg: Ping, ctx: &mut Context<Self, Self::Reply>) {
            ctx.forward(&self.0, msg).await;
        }
    }

    #[tokio::test]
    async fn ask() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        let reply = actor_ref.ask(Ping(12)).await.unwrap();
        assert_eq!(reply, Pong(12));

        assert_eq!(spy.ping.recv().await.unwrap(), Ping(12));
    }

    #[tokio::test]
    async fn ask_enqueue() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        let pending_reply = actor_ref.ask_enqueue(Ping(12)).await.unwrap();
        assert_eq!(pending_reply.recv().await.unwrap(), Pong(12));

        assert_eq!(spy.ping.recv().await.unwrap(), Ping(12));
    }

    #[tokio::test]
    async fn tell() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        actor_ref.tell(Ping(12)).await.unwrap();

        assert_eq!(spy.ping.recv().await.unwrap(), Ping(12));
    }

    #[tokio::test]
    async fn tell_blocking() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        let other = actor_ref.clone();
        tokio::task::spawn_blocking(move || other.tell_blocking(Ping(12)).unwrap())
            .await
            .unwrap();

        assert_eq!(spy.ping.recv().await.unwrap(), Ping(12));
    }

    #[tokio::test]
    async fn ask_no_reply() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        let err = actor_ref.ask(Bang(12)).await.unwrap_err();
        assert_eq!(err, SendError::NoReply);

        assert_eq!(spy.bang.recv().await.unwrap(), Bang(12));
    }

    #[tokio::test]
    async fn tell_no_reply() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        actor_ref.tell(Bang(12)).await.unwrap();

        assert_eq!(spy.bang.recv().await.unwrap(), Bang(12));
    }

    #[tokio::test]
    async fn forward() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        let actor = ForwardingActor(actor_ref);
        let actor_ref = spawn(actor);

        let reply = actor_ref.ask(Ping(12)).await.unwrap();
        assert_eq!(reply, Pong(12));

        assert_eq!(spy.ping.recv().await.unwrap(), Ping(12));
    }

    #[tokio::test]
    async fn started_and_stopped() {
        let (actor, spy) = TestActor::new();
        let actor_ref = spawn(actor);

        let reply = actor_ref.ask(Ping(12)).await.unwrap();
        assert_eq!(reply, Pong(12));

        assert!(spy.started.load(Ordering::Acquire));
        assert!(!spy.stopped.load(Ordering::Acquire));

        actor_ref.stop_gracefully().await.unwrap();
        actor_ref.wait_for_stop().await;

        assert!(spy.stopped.load(Ordering::Acquire));
    }

    #[tokio::test]
    async fn stop() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        actor_ref.tell(Ping(12)).await.unwrap();
        actor_ref.stop_gracefully().await.unwrap();

        assert_eq!(spy.ping.recv().await.unwrap(), Ping(12));

        actor_ref.wait_for_stop().await;
    }

    #[tokio::test]
    async fn kill() {
        let (actor, mut spy) = TestActor::new();
        let actor_ref = spawn(actor);

        actor_ref.tell(Ping(12)).await.unwrap();
        actor_ref.kill();

        assert!(spy.ping.recv().await.is_none());

        actor_ref.wait_for_stop().await;
    }

    #[tokio::test]
    async fn wait_for_stop() {
        let (actor, _) = TestActor::new();
        let actor_ref = spawn(actor);

        let other = actor_ref.clone();
        let wait_handle = tokio::task::spawn(async move { other.wait_for_stop().await });

        tokio::task::yield_now().await;
        assert!(!wait_handle.is_finished());

        actor_ref.stop_gracefully().await.unwrap();

        wait_handle.await.unwrap();
    }
}
